import { NgModule } from '@angular/core';
import { MatButtonModule, MatCheckboxModule, MatInputModule, MatSelectModule, MatSnackBarModule } from '@angular/material';
import { MatButtonToggleModule } from '@angular/material/button-toggle';
import { MatCardModule } from '@angular/material/card';
import { MatExpansionModule } from '@angular/material/expansion';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatListModule } from '@angular/material/list';
import { MatMenuModule } from '@angular/material/menu';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatRadioModule } from '@angular/material/radio';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatTabsModule } from '@angular/material/tabs';
import { MatToolbarModule } from '@angular/material/toolbar';

@NgModule({
    imports: [MatSnackBarModule, MatSelectModule, MatButtonToggleModule, MatCheckboxModule, MatInputModule, MatFormFieldModule, MatExpansionModule, MatTabsModule, MatMenuModule, MatButtonModule, MatIconModule, MatProgressSpinnerModule, MatRadioModule, MatToolbarModule, MatSidenavModule, MatCardModule, MatListModule],
    exports: [MatSnackBarModule, MatSelectModule, MatButtonToggleModule, MatCheckboxModule, MatInputModule, MatFormFieldModule, MatExpansionModule, MatTabsModule, MatMenuModule, MatButtonModule, MatIconModule, MatProgressSpinnerModule, MatRadioModule, MatToolbarModule, MatSidenavModule, MatCardModule, MatListModule],
})

export class MaterialModule { }
