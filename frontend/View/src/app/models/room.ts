
export class Room {

  constructor(
    public name: string,
    public maxPersonCount: number,
    public floorId: number,

    public posX: number,
    public posY: number,
    public width: number,
    public height: number,

    public id?: number,
    public iotDeviceId?: number,

  ) { }
}

export function isRoom(arg: any): arg is Room {
  if (typeof arg.id !== 'number') { return false; }
  if (typeof arg.name !== 'string') { return false; }
  if (typeof arg.maxPersonCount !== 'number') { return false; }
  if (typeof arg.floorId !== 'number') { return false; }

  if (typeof arg.posX !== 'number') { return false; }
  if (typeof arg.posY !== 'number') { return false; }
  if (typeof arg.width !== 'number') { return false; }
  if (typeof arg.height !== 'number') { return false; }

  return true;
}

export function isRoomArray(arg: any): arg is Room[] {
  if (!Array.isArray(arg)) { return false; }
  for (const floor of arg) {
    if (!isRoom(floor)) { return false; }
  }
  return true;
}

