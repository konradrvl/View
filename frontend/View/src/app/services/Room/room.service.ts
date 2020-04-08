import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { createOccupationByString, Occupation } from '../../models/occupation';
import { isOccupationDateStringArray } from '../../models/occupationDateString';
import { isRoom, isRoomArray, Room } from '../../models/room';

@Injectable({
  providedIn: 'root'
})
export class RoomService {

  private static readonly URL: string = '/api/rooms';

  constructor(private http: HttpClient) { }

  public async getRoom(roomId: number): Promise<Room> {

    const res = await this.http.get(`${RoomService.URL}/${roomId}`).toPromise();

    if (isRoom(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async getRooms(floorId: number): Promise<Room[]> {

    const res = await this.http.get(`${RoomService.URL}`, { params: { 'floorId': `${floorId}` } }).toPromise();

    if (isRoomArray(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async createRoom(newRoom: Room): Promise<Room> {

    const res = await this.http.post(`${RoomService.URL}`, newRoom).toPromise();

    if (isRoom(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async editRoom(roomId: number, newRoom: Room): Promise<Room> {

    const res = await this.http.put(`${RoomService.URL}/${roomId}`, newRoom).toPromise();

    if (isRoom(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async deleteRoom(roomId: number) {

    await this.http.delete(`${RoomService.URL}/${roomId}`).toPromise();

  }

  public async getRoomHistory(roomId: number, from: Date, to: Date): Promise<Occupation[]> {
    const occupationURL = '/api/occupations/history';

    const params = {
      roomId: roomId.toString(),
      from: from.toISOString(),
      to: to.toISOString()
    };

    const res = await this.http.get(occupationURL, { params }).toPromise();

    if (isOccupationDateStringArray(res)) {
      return res.map(createOccupationByString);
    }

    throw new Error('Invalid Response');
  }
}
