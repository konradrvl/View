import { Injectable } from '@angular/core';
import * as Rx from 'rxjs';
import { filter } from 'rxjs/operators';
import { isMessage, Message } from '../../models/message';

@Injectable({
  providedIn: 'root'
})
export class WebsocketService {

  private static readonly URL: string = `ws://${window.location.host}/api/occupations/ws-frontend`;

  private webSocket: WebSocket;

  private _subscriptions: Set<number> = new Set;

  private subject: Rx.Subject<Message> = new Rx.Subject();

  constructor() {
    this.initWebsocket();
  }

  private initWebsocket(subscriptions?: Set<number>) {
    this.webSocket = new WebSocket(WebsocketService.URL);

    this.webSocket.onopen = () => {
      if (subscriptions) {
        this.webSocket.send(JSON.stringify(Array.from(subscriptions.values())));
      }
      console.log('Connected!');
    }

    this.webSocket.onmessage = msg => {
      const data = JSON.parse(msg.data);
      if (isMessage(data)) {
        this.subject.next({ roomId: data.roomId, personCount: data.personCount });
      }
    };

    this.webSocket.onclose = async () => {
      this.subject.next({ roomId: 0, personCount: -1 });
      this.tryToReconnect();
    }
  }

  private async tryToReconnect() {
    await sleep(5000);
    console.log('Reconnecting...');
    this.initWebsocket(this._subscriptions);
  }

  public subscribe(roomId: number, cb: (value: number) => void) {
    // TODO: add possibilty to request multiple WS Connections with an array of roomId
    this.webSocket.send(JSON.stringify([roomId]));
    this.subject.pipe(filter(x => x.roomId === roomId || x.roomId === 0)).subscribe(x => cb(x.personCount));
    this._subscriptions.add(roomId);
  }

}

function sleep(ms = 0) {
  return new Promise(r => setTimeout(r, ms));
}
