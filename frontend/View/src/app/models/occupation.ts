import { OccupationDateString } from './occupationDateString';

export class Occupation {

  constructor(
    public id: number,
    public roomId: number,
    public time: Date,
    public personCount: number,
  ) { }

}

export function createOccupationByString(occupation: OccupationDateString): Occupation {
  return new Occupation(occupation.id, occupation.roomId, new Date(occupation.time), occupation.personCount);
}

export function isOccupation(arg: any): arg is Occupation {
  if (typeof arg.id !== 'number') { return false; }
  if (typeof arg.roomId !== 'number') { return false; }
  return true;
}

export function isOccupationArray(arg: any): arg is Occupation[] {
  if (!Array.isArray(arg)) { return false; }
  for (const occupation of arg) {
    if (!isOccupation(occupation)) { return false; }
  }
  return true;
}
