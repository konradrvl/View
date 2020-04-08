export class IoTDevice {

    constructor(
        public id: string,
        public userId: number,
    ) { }
}

export function isIoTDevice(arg: any): arg is IoTDevice {
    if (typeof arg.id !== 'string') { return false; }
    if (typeof arg.userId !== 'number') { return false; }
    return true;
}

export function isIoTDeviceArray(arg: any): arg is IoTDevice[] {
    if (!Array.isArray(arg)) { return false; }
    for (const floor of arg) {
        if (!isIoTDevice(floor)) { return false; }
    }
    return true;
}
