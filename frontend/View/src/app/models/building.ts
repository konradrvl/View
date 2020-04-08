
export class Building {


  constructor(
    public name: string,
    public id?: number) {
  }

}

export function isBuilding(arg: any): arg is Building {
  if (typeof arg.id !== 'number') { return false; }
  if (typeof arg.name !== 'string') { return false; }
  return true;
}

export function isBuildingArray(arg: any): arg is Building[] {
  if (!Array.isArray(arg)) { return false; }
  for (const building of arg) {
    if (!isBuilding(building)) { return false; }
  }
  return true;
}
