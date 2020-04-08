import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Building, isBuilding, isBuildingArray } from '../../models/building';

@Injectable({
  providedIn: 'root'
})
export class BuildingService {

  private static readonly URL: string = '/api/buildings';

  constructor(private http: HttpClient) { }

  public async getBuilding(id: number): Promise<Building> {

    const res = await this.http.get(`${BuildingService.URL}/${id}`).toPromise();

    if (isBuilding(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async getBuildings(): Promise<Building[]> {

    const res = await this.http.get(`${BuildingService.URL}`).toPromise();

    if (isBuildingArray(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async createBuilding(newBuilding: Building): Promise<Building> {

    const res = await this.http.post(`${BuildingService.URL}`, newBuilding).toPromise();

    if (isBuilding(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async editBuilding(id: number, newBuilding: Building): Promise<Building> {

    const res = await this.http.put(`${BuildingService.URL}/${id}`, newBuilding).toPromise();

    if (isBuilding(res)) {
      return res;
    }

    throw new Error('Invalid response');
  }

  public async deleteBuilding(id: number) {

    await this.http.delete(`${BuildingService.URL}/${id}`).toPromise();

  }
}
