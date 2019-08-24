#include <stdio.h>
#include <math.h>
#include <string.h>

char lakenames[6][9];
double lake_ave[2][6];
double lake_warmest[3][6];
double lake_coldest[3][6];
int coldest_days[365];
double overall_avg;

void swap (double *arr1, double *arr2) {
	double temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

void convert_date(int date) {


	if(date <= 59 && date > 0) {
		if (date <= 31) {
			printf("On 01/%-.2d ", date);
		}
		else{
			printf("On 02/%-.2d ", date-31);
		}
	}
	else if (date > 59) {
		if(date <= 90)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-59);
		else if(date <= 120)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-90);
		else if(date <= 151)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-120);
		else if(date <= 181)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-151);
		else if(date <= 212)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-181);
		else if(date <= 243)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-212);
		else if(date <= 273)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-243);
		else if(date <= 304)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-273);
		else if(date <= 334)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-304);
		else if(date < 365)
			printf("On %-.2d/%-.2d ", (int)ceil(date/30.41), date-334);
		else if (date == 365)
			printf("On %-.2d/%-.2d ", (int)floor(date/30.41), date-334);
	}

}

void call_lakename(double lake_counter) {

	if (lake_counter == 0.0)
		printf("Lake %s ",lakenames[0]);
	else if (lake_counter == 1.0)
		printf("Lake %s ",lakenames[1]);
	else if (lake_counter == 2.0)
		printf("Lake %s ",lakenames[2]);  
	else if (lake_counter == 3.0)
		printf("Lake %s ",lakenames[3]);
	else if (lake_counter == 4.0)
		printf("Lake %s ",lakenames[4]);
	else if (lake_counter == 5.0)
		printf("Lake %s ",lakenames[5]);
	
}

double func_1 (double data[365][8], char label[6][9]) {
	int day = 0;
	int count = 0,  i=0;
	double day_temp, avg = 0.0;

        
   for (count = 2; count < 8; count++) {
     lake_ave[0][count-2] = (count-2)*1.0;
          for(day = 0; day < 365; day++) {
          
          	 day_temp = data[day][count];
          	 avg = day_temp + avg;
			 
          }
  
        lake_ave[1][count-2] = avg/365;	   
        printf("Average Temperature for Lake %s is %.2lf Celsius\n", label[count-2], lake_ave[1][count-2]);
		avg = 0.0;	  
       }
	   
	for(i = 0; i < 6; i++) {
		overall_avg = lake_ave[1][i] + overall_avg;
	}	 
	overall_avg = overall_avg/6.0;	  
	printf("Overall A\average of all the lakes is %.2lf Celsius\n", overall_avg);
	
}
	    
void func_2 (double data[365][8], char label[6][9]) {
	int i, x;
	for (x = 0; x < 5; x++) {	 	 
		for(i = 0; i < 5-x; i++) {
			if(lake_ave[1][i] > lake_ave[1][i+1]) {
				swap(&lake_ave[1][i], &lake_ave[1][i+1]);
				swap(&lake_ave[0][i], &lake_ave[0][i+1]);	    
			}	 	 	 	 	 
		}	 
	}
	
	call_lakename(lake_ave[0][5]);
	printf("has the warmest average temperature at %.2lf Celsius\n", lake_ave[1][5]);
	call_lakename(lake_ave[0][0]);
	printf("has the coldest average temperature at %.2lf Celsius\n", lake_ave[1][0]);

	for (i = 0; i < 6; i++) {
		
		if(lake_ave[1][i] > overall_avg) {
			printf("Lake %s is above the average\n", label[i]);	   	   
			
		}else {
			printf("Lake %s is below the average\n", label[i]);	   	   
		
		}	 
	}

}

void func_3 (double lake_data[365][8], char label[6][9]) {
	int x,i;
	double coldest, warmest;
	for (i = 0; i <365; i++) {
		coldest_days[i] = 0;
	
	}
		
	for (x = 2; x < 8; x++) {
		lake_warmest[0][x-2] = 1.0*(x-2);
		lake_coldest[0][x-2] = 1.0*(x-2);

		coldest = lake_data[0][x];
		warmest = lake_data[0][x];
		
		for (i = 0; i < 365; i++) {
			if (warmest < lake_data[i][x]) {
				warmest = lake_data[i][x];
				lake_warmest[2][x-2] = i+1; 
			}	 
			if (coldest > lake_data[i][x]) {
			
				coldest = lake_data[i][x];
				lake_coldest[2][x-2] = i+1;
			}
			/*
				lists all the coldest dates for St. Clair
			*/	  
			if(lake_data[i][x] == 0.21) {
				coldest_days[i] = i+1;
			}  
			  	
		}
		
	lake_warmest[1][x-2] = warmest;
	lake_coldest[1][x-2] = coldest;
	}	
	
	for (i = 0; i < 6; i++) {
		convert_date(((int)lake_warmest[2][i]));
		printf("Lake %s acquired an overall warmest temperature of %.2lf Celsius\n",label[i], lake_warmest[1][i]);

		convert_date(((int)lake_coldest[2][i]));
		printf("it acquired an overall coldest temperature of %.2lf Celsius\n", lake_coldest[1][i]);
		
	}
}


void func_4(double lake_data[365][8]) {
	int i, x;
	
	for (x = 0; x < 5; x++) {	 	 
		for(i = 0; i < 5-x; i++) {
			if(lake_warmest[1][i] > lake_warmest[1][i+1]) {
				swap(&lake_warmest[1][i], &lake_warmest[1][i+1]);
				swap(&lake_warmest[0][i], &lake_warmest[0][i+1]);	
			}	
			
			if(lake_coldest[1][i] > lake_coldest[1][i+1]) {
				swap(&lake_coldest[1][i], &lake_coldest[1][i+1]);
				swap(&lake_coldest[0][i], &lake_coldest[0][i+1]);	
			}		   	   	   	   
		}	 
	}
	
	convert_date(((int)lake_warmest[2][5])); 
	printf("The lake that acquired the warmest overall temperature is ");
	call_lakename(lake_warmest[0][5]);
	printf("at %.2lf Celsius\n", lake_warmest[1][5]);
		   
	
	printf("The lake that acquired coldest overall temparature is ");
	call_lakename(lake_coldest[0][0]);	
	printf("at %.2lf Celsius\n", lake_coldest[1][0]);  	   	      	             	    	             	  
	printf("The coldest temperature was acquired on these dates: \n");
	for( i = 0; i < 365; i++) {
		if (coldest_days[i] != 0) {
			convert_date(coldest_days[i]);
			printf(", ");
		}
	} 
	printf("\n");	  
}


void func_5(double lake_data[365][8]) {
	double sum;
	double summer_average[2][6];
	int x,i;	
		
	for (x = 2; x < 8; x++) {
		sum = 0.0;
		summer_average[0][x-2] = 1.0*(x-2);
		
		
		for(i = 171; i < 265; i++) {
			sum += lake_data[i][x];
		}	
		summer_average[1][x-2] = sum/(1.0*(94));
	}
			
	for (x = 0; x < 5; x++) {	 	 
		for(i = 0; i < 5-x; i++) {
			if(summer_average[1][i] > summer_average[1][i+1]) {
				swap(&summer_average[1][i], &summer_average[1][i+1]);
				swap(&summer_average[0][i], &summer_average[0][i+1]);	 
			}	 	 	 	 	 
		}	 
	}
	
	printf("The summer average for all 6 lakes listed from warmest to coldest are:\n");
	for(i = 5; i >= 0; i--) {
		call_lakename(summer_average[0][i]);
		printf("at %.2lf Celsius\n", summer_average[1][i]);               
	}	 
}


void func_6(double lake_data[365][8]) {	   
	double sum;
	double sum2;
	double winter_average[2][6];
	int x,i;	
		
	for (x = 2; x < 8; x++) {
		sum = 0.0;
		sum2 = 0.0;	   
		winter_average[0][x-2] = 1.0*(x-2);
		
		for(i = 0; i < 79; i++) {
			sum += lake_data[i][x];
		}
		for(i = 354; i < 365; i++) {
			sum2 += lake_data[i][x];
		}
		winter_average[1][x-2] = (sum+sum2)/(1.0*(90));
	}
				
	for (x = 0; x < 5; x++) {	 	 
		for(i = 0; i < 5-x; i++) {
			if(winter_average[1][i] > winter_average[1][i+1]) {
				swap(&winter_average[1][i], &winter_average[1][i+1]);
				swap(&winter_average[0][i], &winter_average[0][i+1]);	 
			}	 	 	 	 	 
		}	 
	}
	
	printf("The winter average for all 6 lakes listed from warmest to coldest are:\n");
	for(i = 5; i >= 0; i--) {
		call_lakename(winter_average[0][i]);
		printf("at %.2lf Celsius\n", winter_average[1][i]);              
	}	 
}


void func_7(double data[365][8],char label[6][9])
{
	int i,j,counter;
	int freezedays[5];
	int arrayvalue =0;
	
	for (j=2;j<8;j++)
	{
		
		counter = 0;
		for(i=0;i<365;i++)
		{
			if((data[i][0]) < 0)
			{
				counter++;
			}
		}
		freezedays[j-2] = counter;
		arrayvalue++;
	}
	
	
	printf("Days that the water was frozen (<0 degrees)\n");
	for(j=0;j<6;j++)
	{
	printf("%4s:",label[j]);
	printf("%5d\n",freezedays[j]);
	}

}


void func_8(double data[365][8], char label[6][9])
{
	int i,j,counter;
	int warmdays[6];
	
	for (j=2;j<8;j++)
	{
		counter = 0;
		for(i=0;i<365;i++)
		{
			if(data[i][j] >= 20)
			{
				counter++;
			}
		}
		warmdays[j-2] = counter;
	}
	
	printf("Days that the water was warm (>20 degrees)\n");
	for(j=0;j<6;j++)
	{
	printf("%4s:",label[j]);
	printf("%5d\n",warmdays[j]);
	}
}


int main (){

	FILE *data = fopen("data.txt","r");
	
	double lakedata[365][8];
	int i=0;
	int j=0;
	
	
	strcpy(lakenames[0], "Superior");
	strcpy(lakenames[1], "Michigan");
	strcpy(lakenames[2], "Huron");
	strcpy(lakenames[3], "Erie");
	strcpy(lakenames[4], "Ontario");
	strcpy(lakenames[5], "St. Clair");
	
	
	for(i=0;i<365;i++)
	{
		for(j=0;j<8;j++)
		{
			fscanf(data,"%lf",&lakedata[i][j]);
		}
	}
	fclose(data);
	
	/* THIS JUST DISPLAYS THE DATA */
	/*
	for(i=0;i<365;i++)	  
	{	
		for(j=0;j<8;j++)
		{
			printf("%7.2lf  ",lakedata[i][j]);
		}
		printf("\n");
	}
	*/
	
	/* INSERT YOUR FUNCTION CALLS HERE TO TEST INTEGRATION! */
		
	func_1(lakedata,lakenames);
	printf("\n");
	func_2(lakedata,lakenames);
	printf("\n");
	func_3(lakedata,lakenames);
	printf("\n");
	func_4(lakedata);
	printf("\n");
	func_5(lakedata);
	printf("\n");
	func_6(lakedata);
	printf("\n");
	func_7(lakedata,lakenames);
	printf("\n");
	func_8(lakedata,lakenames);
	
	
	return(0);
	
}


