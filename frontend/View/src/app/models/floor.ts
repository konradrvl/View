
export class Floor {


  constructor(
    public name: string,
    public buildingId: number,
    public id?: number
  ) { }
}

export function isFloor(arg: any): arg is Floor {
  if (typeof arg.id !== 'number') { return false; }
  if (typeof arg.name !== 'string') { return false; }
  if (typeof arg.buildingId !== 'number') { return false; }
  return true;
}

export function isFloorArray(arg: any): arg is Floor[] {
  if (!Array.isArray(arg)) { return false; }
  for (const floor of arg) {
    if (!isFloor(floor)) { return false; }
  }
  return true;
}
