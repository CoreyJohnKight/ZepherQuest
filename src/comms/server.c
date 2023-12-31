#include "comms/server.h"
#include "io/read.h"

static const char *TAG_SERVER = "http server";
extern TaskHandle_t xReadTask_handle;
extern SemaphoreHandle_t xReadingCompleteSemaphore;
extern volatile uint16_t dataValue;

/* A function to handle common request processing for all endpoints */
static void common_request_handler(httpd_req_t *req)
{
    char *buf;
    size_t buf_len;

    /* Get and process headers.
    Currentley displaying HOST, more options available for future use. */
    const char *header_names[] = {"Host", "Test-Header-2", "Test-Header-1"};
    for (int i = 0; i < sizeof(header_names) / sizeof(header_names[0]); i++)
    {
        buf_len = httpd_req_get_hdr_value_len(req, header_names[i]) + 1;
        if (buf_len > 1)
        {
            buf = malloc(buf_len);
            if (httpd_req_get_hdr_value_str(req, header_names[i], buf, buf_len) == ESP_OK)
            {
                ESP_LOGI(TAG_SERVER, "Found header => %s: %s", header_names[i], buf);
            }
            free(buf);
        }
    }

    /* Process URL queries.
    TODO: For future use. */
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG_SERVER, "Found URL query => %s", buf);
            char param[32];
            const char *query_params[] = {"query1", "query2", "query3"};
            for (int i = 0; i < sizeof(query_params) / sizeof(query_params[0]); i++)
            {
                if (httpd_query_key_value(buf, query_params[i], param, sizeof(param)) == ESP_OK)
                {
                    ESP_LOGI(TAG_SERVER, "Found URL query parameter => %s=%s", query_params[i], param);
                }
            }
        }
        free(buf);
    }
}

/* An HTTP GET handler for the /favicon.ico request.
Respond null so that no error is generated. */
static esp_err_t favicon_get_handler(httpd_req_t *req)
{
    common_request_handler(req);

    ESP_LOGI(TAG_SERVER, "Responding NULL to favIcon");

    httpd_resp_send(req, NULL, 0);

    return ESP_OK;
}

/* HTTP GET handler for /hello
Wakes up the reader, waits for read to complete, then responds with the data*/
static esp_err_t hello_get_handler(httpd_req_t *req)
{
    // Apply common handling
    common_request_handler(req);

    // Set some custom headers
    // TODO: Future use
    httpd_resp_set_hdr(req, "Custom-Header-1", "Custom-Value-1");
    httpd_resp_set_hdr(req, "Custom-Header-2", "Custom-Value-2");

    ESP_LOGI(TAG_SERVER, "Waiting for reading to complete");

    // Give the semaphore to signal the reader
    xSemaphoreGive(xReadingCompleteSemaphore);

    if (xSemaphoreTake(xReadingCompleteSemaphore, config_SERVER_RESPOND_TIMEOUT / portTICK_PERIOD_MS) == pdTRUE)
    {
        ESP_LOGI(TAG_SERVER, "Responding to HELLO");

        // Convert dataValue to a string
        char strDataValue[16]; // Assuming a maximum of 16 characters for the integer value
        snprintf(strDataValue, sizeof(strDataValue), "%d", dataValue);

        // Create a buffer to hold the updated response string
        char updatedRespStr[256]; // Adjust the buffer size as needed
        snprintf(updatedRespStr, sizeof(updatedRespStr), "%s DataValue: %s", (const char *)req->user_ctx, strDataValue);

        // Send response with custom headers and body set as the
        // string passed in user context
        httpd_resp_send(req, updatedRespStr, HTTPD_RESP_USE_STRLEN);

        // After sending the HTTP response the old HTTP request
        // headers are lost. Check if HTTP request headers can be read now.
        if (httpd_req_get_hdr_value_len(req, "Host") == 0)
        {
            ESP_LOGI(TAG_SERVER, "Request headers lost");
        }
        return ESP_OK;
    }
    else
    {
        // Timeout
        ESP_LOGI(TAG_SERVER, "Timeout waiting for response from reader");

        return ESP_FAIL;
    }
}

//-------------------------------------------------------------------

/* Register the /favicon.ico request handler */
static const httpd_uri_t favicon =
    {
        .uri = "/favicon.ico",
        .method = HTTP_GET,
        .handler = favicon_get_handler,
        .user_ctx = NULL};

/* Register the /hello request handler */
static const httpd_uri_t hello =
    {
        .uri = "/hello",
        .method = HTTP_GET,
        .handler = hello_get_handler,
        .user_ctx = "Hello, this is the esp32 speaking.",
};

// Start the HTTP server
httpd_handle_t
start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    config.lru_purge_enable = true;

    ESP_LOGI(TAG_SERVER, "Starting server on port: '%d'", config.server_port);

    // Register the requests
    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &hello);
        httpd_register_uri_handler(server, &favicon);
        return server;
    }

    ESP_LOGI(TAG_SERVER, "Error starting server!");
    return NULL;
}
