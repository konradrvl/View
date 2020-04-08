namespace View.Server.Shared.IoTAccess
{
    public interface IIoTAccess
    {
        event WsIotDelegates.IoTDeviceLoginRequestedDelegate IoTDeviceLoginRequested;
        event WsIotDelegates.PersonCountChangedDelegate PersonCountChanged;
        event WsIotDelegates.RoomInvalidatedDelegate RoomInvalidated;
        
        void Start();
        void Stop();
        void SetInvalid(string iotDeviceId);
        void SetValid(string iotDeviceId);
        void SetRoom(string iotDeviceId, int roomId);
        void DeleteRoom(int roomId);
        void RequestCurrentValue(int roomId);
    }
}