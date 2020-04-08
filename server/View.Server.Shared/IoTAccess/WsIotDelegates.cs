using System;

namespace View.Server.Shared.IoTAccess
{
    public static class WsIotDelegates
    {
        public delegate void IoTDeviceLoginRequestedDelegate(string iotDeviceId);

        public delegate void PersonCountChangedDelegate(int roomId, int personCount, DateTime timeStamp);

        public delegate void RoomInvalidatedDelegate(int roomId);
    }
}