export class OccupationDateString {

  constructor(
    public id: number,
    public roomId: number,
    public time: string,
    public personCount: number,
  ) { }

}

export function isOccupationDateString(arg: any): arg is OccupationDateString {
  if (typeof arg.id !== 'number') { return false; }
  if (typeof arg.roomId !== 'number') { return false; }
  if (typeof arg.personCount !== 'number') { return false; }
  if (typeof arg.time !== 'string') { return false; }
  return true;
}

export function isOccupationDateStringArray(arg: any): arg is OccupationDateString[] {
  if (!Array.isArray(arg)) { return false; }
  for (const occupation of arg) {
    if (!isOccupationDateString(occupation)) { return false; }
  }
  return true;
}
