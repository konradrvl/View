using System;
using System.Collections.Generic;
using View.Server.Shared.DataAccesses;
using View.Server.Shared.IoTAccess;

namespace View.Server.Service.Stores
{
    public class OcupationServiceStore
    {
        public event Action<int, int> PersonCountChanged;

        private readonly Dictionary<int, int> _liveData = new Dictionary<int, int>();

        private readonly IIoTAccess _ioTAccess;

        private readonly IOccupationDataAccess _occupationDataAccess;
        private readonly IRoomDataAccess _roomDataAccess;
        private readonly IIoTDeviceDataAccess _ioTDeviceDataAccess;

        public OcupationServiceStore(IIoTAccess ioTAccess, IOccupationDataAccess occupationDataAccess,
            IRoomDataAccess roomDataAccess, IIoTDeviceDataAccess ioTDeviceDataAccess)
        {
            _ioTAccess = ioTAccess;

            _occupationDataAccess = occupationDataAccess;
            _roomDataAccess = roomDataAccess;
            _ioTDeviceDataAccess = ioTDeviceDataAccess;

            _ioTAccess.PersonCountChanged += AddOccupation;
            _ioTAccess.RoomInvalidated += InvalidRoom;
            _ioTAccess.IoTDeviceLoginRequested += ValidateIoTDevice;
        }

        public int GetCurrentPersonCount(int roomId)
        {
            lock (_liveData)
            {
                return _liveData.GetValueOrDefault(roomId, -1);
            }
        }

        private async void AddOccupation(int roomId, int personCount, DateTime time)
        {
            int? currentValue = null;

            lock (_liveData)
            {
                if (_liveData.ContainsKey(roomId))
                {
                    currentValue = _liveData[roomId];
                }

                _liveData[roomId] = personCount;
            }

            if (currentValue == null || currentValue != personCount)
            {
                var task = _occupationDataAccess.AddOccupation(roomId, personCount, time);
                PersonCountChanged?.Invoke(roomId, personCount);
                await task;
            }
        }

        private async void InvalidRoom(int roomId)
        {
            var task = _occupationDataAccess.AddOccupation(roomId, -1, DateTime.Now);

            lock (_liveData)
            {
                _liveData.Remove(roomId);
            }

            PersonCountChanged?.Invoke(roomId, -1);
            await task;
        }

        private async void ValidateIoTDevice(string iotDeviceId)
        {
            if (await _ioTDeviceDataAccess.IoTDeviceExists(iotDeviceId))
            {
                _ioTAccess.SetValid(iotDeviceId);

                var room = await _roomDataAccess.GetRoomByIoTDeviceId(iotDeviceId);

                if (room != null)
                {
                    _ioTAccess.SetRoom(iotDeviceId, room.Id);
                }
            }
            else
            {
                _ioTAccess.SetInvalid(iotDeviceId);
            }
        }
    }
}