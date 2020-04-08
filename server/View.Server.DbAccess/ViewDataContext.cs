using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using View.Server.Shared.Data;
using View.Server.Shared.Data.UserManagement;
// ReSharper disable UnusedMember.Global
// ReSharper disable UnusedAutoPropertyAccessor.Global

namespace View.Server.DbAccess
{
    public sealed class ViewDataContext : DbContext
    {
        public DbSet<Building> Buildings { get; set; }
        public DbSet<Floor> Floors { get; set; }
        public DbSet<Room> Rooms { get; set; }
        public DbSet<IoTDevice> IoTDevices { get; set; }
        public DbSet<Occupation> Occupations { get; set; }
        public DbSet<User> Users { get; set; }

        public DbSet<IdentityUserClaim<int>> IdentityUserClaims { get; set; }
        public DbSet<IdentityUserRole<int>> IdentityUserRoles { get; set; }
        public DbSet<IdentityRole<int>> IdentityRoles { get; set; }

        public ViewDataContext(DbContextOptions options) : base(options)
        {
            if (Database.EnsureCreated())
            {
                //Create 10 unused IoT-Devices
                Database.ExecuteSqlCommand("INSERT INTO `IoTDevices` (`Id`) VALUES ('1');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('2');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('3');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('4');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('5');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('6');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('7');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('8');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('9');" +
                                           "INSERT INTO `IoTDevices` (`Id`) VALUES ('10');");
            }
            
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            
            modelBuilder.Entity<IoTDevice>().Property(x => x.Id).HasMaxLength(100).IsRequired();
            
            modelBuilder.Entity<IdentityUserRole<int>>().HasKey(p => new { p.UserId, p.RoleId });
            
            modelBuilder.Entity<IoTDevice>()
                .HasOne(x => x.User)
                .WithMany(x => x.IoTDevices)
                .HasForeignKey(x => x.UserId)
                .IsRequired(false);

            modelBuilder.Entity<Room>()
                .HasOne(x => x.IoTDevice)
                .WithOne(x => x.Room)
                .HasForeignKey<Room>(x => x.IoTDeviceId)
                .IsRequired(false);
        }
    }
}