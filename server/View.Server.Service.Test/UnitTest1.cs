using System.IO;
using Microsoft.Extensions.Configuration;
using Xunit;

namespace View.Server.Service.Test
{
    public class BuildingServiceTest
    {
        [Fact]
        public void Test1()
        {
            var config = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory()+"../View.Server.WebAPI")
                .AddJsonFile("appsettings.json")
                .Build();
        }
    }
}