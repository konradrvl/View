export class Message {

    constructor(
        public roomId: number,
        public personCount: number) { }

}

export function isMessage(arg: any): arg is Message {
    if (typeof arg.roomId !== 'number') { return false; }
    if (typeof arg.personCount !== 'number') { return false; }
    return true;
}
