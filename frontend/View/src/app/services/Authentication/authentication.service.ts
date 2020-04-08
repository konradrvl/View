import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {

  private static readonly URL: string = '/api/user';

  constructor(private http: HttpClient) { }

  public async login(username: string, password: string, keepLoggedIn: boolean) {
    await this.http.post(AuthenticationService.URL, { username, password, keepLoggedIn }).toPromise();
  }

  public async register(username: string, password: string) {
    await this.http.post(`${AuthenticationService.URL}/register`, { username, password }).toPromise();
  }

  public async isLoggedin() {
    try {
      await this.http.get(`${AuthenticationService.URL}/check`).toPromise();
      return true;
    } catch (e) {
      console.log(e);
      return false;
    }
  }
}
