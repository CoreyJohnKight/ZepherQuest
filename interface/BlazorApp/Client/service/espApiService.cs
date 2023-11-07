using System.Net.Http;
using System.Threading.Tasks;

namespace BlazorApp.Client.services
{
    public class EspApiService
    {
        private readonly HttpClient _httpClient;

        public EspApiService(HttpClient httpClient)
        {
            _httpClient = httpClient;
        }

        public async Task<int> GetHelloIntFromEspAsync()
        {
            var response = await _httpClient.GetStringAsync("http://192.168.1.35/hello");
            Console.WriteLine("Response: " + response);

            if (int.TryParse(response, out int result))
            {
                return result;
            }

            return 0;
        }
    }
}
