import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MatButtonModule } from '@angular/material';
import {MatIconModule} from '@angular/material/icon';
import {MatProgressSpinnerModule} from '@angular/material/progress-spinner';
import {MatRadioModule} from '@angular/material/radio';
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatSidenavModule} from '@angular/material/sidenav';
import {MatCardModule} from '@angular/material/card';
import {MatListModule} from '@angular/material/list';
import {MatMenuModule} from '@angular/material/menu';
import {MatInputModule} from '@angular/material/input';
import {MatSnackBarModule} from '@angular/material/snack-bar';



@NgModule({
    imports: [MatSnackBarModule, MatInputModule, MatMenuModule, MatButtonModule, MatIconModule,MatProgressSpinnerModule,MatRadioModule,MatToolbarModule,MatSidenavModule,MatCardModule,MatListModule],
    exports: [MatSnackBarModule,MatInputModule, MatMenuModule, MatButtonModule, MatIconModule,MatProgressSpinnerModule,MatRadioModule,MatToolbarModule,MatSidenavModule,MatCardModule,MatListModule],
})

export class MaterialModule { }
