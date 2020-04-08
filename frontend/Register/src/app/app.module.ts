import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {FormsModule} from '@angular/forms';

import { AppComponent } from './app.component';
import { WifiComponent } from './wifi/wifi.component';
import { DataService } from './service/data.service';
import { HttpClientModule } from '@angular/common/http';
import { MaterialModule } from './material.module';


@NgModule({
  declarations: [
    AppComponent,
    WifiComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MaterialModule,
    HttpClientModule,
    FormsModule
  ],
  providers: [DataService],
  bootstrap: [AppComponent]
})
export class AppModule { }
