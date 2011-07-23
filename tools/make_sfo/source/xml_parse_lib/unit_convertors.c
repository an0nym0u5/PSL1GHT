/************************************************************************/
/* Unit Convertors - The following routines are convenience functions	*/
/*  for accepting character-string values with optional unit specifiers	*/
/*  and converting them numerically to consistent MKS units.		*/
/*  MKS, or Meters-Kilogramm-Seconds, is the System International (SI)  */
/*  set of base units.							*/
/* 									*/
/* This library allows units to be specified with measurements in data 	*/
/* files, such as XML files, which is common in real user situations,	*/
/* and promotes a key philosopphy of XML: to have self-contained 	*/
/* unambigous storage and transfer of data.				*/
/*									*/
/* --- All the following routines are NOT sensitive to unit's case. ---	*/
/*									*/
/* Routines for accepting values or measurements of the following types	*/
/* are included:							*/
/*	Time, Distance (linear), Boolean, Temperature, Frequency,	*/
/*	Power, DeciBells (dB).						*/ 
/*									*/
/* For example, the accept_distance() routine will accept user input in */
/* the form of:								*/
/*    	35.2 feet							*/
/*      0.1 cm								*/
/*	33 inches							*/
/*	6.2 miles							*/
/*	6.2 Miles							*/
/*	1.9 km								*/
/* and will return the correct values in meters in all cases.		*/
/* In XML, this can be used to parse attribute values that are 		*/
/* specified with units, for example:					*/
/*	<doorway height="78 inches" width="90 cm"/>			*/
/*	<heater setting="25 C"/>					*/
/*	<temperature> 72 degrees F </temperature>			*/
/*									*/
/* For Documentation and Usage Notes, see:				*/
/*				http://xmlparselib.sourceforge.net/	*/
/*									*/
/* Unit_conertors.c - LGPL License:					*/
/*  Copyright (C) 2001, Carl Kindman					*/
/*  This library is free software; you can redistribute it and/or	*/
/*  modify it under the terms of the GNU Lesser General Public		*/
/*  License as published by the Free Software Foundation; either	*/
/*  version 2.1 of the License, or (at your option) any later version.	*/
/*  This library is distributed in the hope that it will be useful,	*/
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of	*/
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU	*/
/*  Lesser General Public License for more details.			*/
/*  You should have received a copy of the GNU Lesser General Public	*/
/*  License along with this library; if not, write to the Free Software	*/
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 */
/*									*/
/* Issues:  Many more units/conversions should be added, such as:	*/
/*	speed, volume, pressure, data-sizes (bits/bytes), data-rates, 	*/
/*	capacitance, inductance, resistance, voltage, current, 		*/
/*	force/weight, acceleration, density, angles (deg/radians), 	*/
/*	area, heat/energy, ...						*/
/*									*/
/*  Carl Kindman 8-21-2001     carl_kindman@yahoo.com			*/
/************************************************************************/



/* Accept distance or length value, and/or convert units to Meters. Return 1 on success, 0 on failure. */
int accept_distance( char *wrd, float *dist )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",dist)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strncasecmp(tval,"Mile",4)==0)  *dist = 1.6093 * *dist;  else
 if ((strcasecmp(tval,"feet")==0) || (strcasecmp(tval,"ft")==0) || (strcasecmp(tval,"foot")==0)) *dist = 0.3048 * *dist;  else
 if ((strncasecmp(tval,"yrd",3)==0) || (strncasecmp(tval,"yard",4)==0))  *dist = 3.0 * 0.3048 * *dist;  else
 if (strncasecmp(tval,"in",4)==0)  *dist = 0.3048 * *dist / 12.0;  else
 if (strcasecmp(tval,"Km")==0)  *dist = *dist * 1e3;  else
 if (strcasecmp(tval,"cm")==0)  *dist = 0.01 * *dist;  else
 if (strcasecmp(tval,"mm")==0)  *dist = 0.001 * *dist;  else
 if ((strlen(tval)!=0) && (strncasecmp(tval,"meter",5)!=0)) { printf("Bad distance unit %s.\n",tval); return 0; }
 return 1;
}


int accept_boolean( char *word )       /* Accept boolean value from valid char-string answers. */
{ char ch;			       /* Returns 1 if true, 0 if false, -1 on error. */
  ch = toupper(word[0]);	       /* Accepts T[rue], Y[es], 1, On, F[alse], N[o], 0, Off. */
  if ((ch=='Y') || (ch=='T') || (ch=='1') || (!strcasecmp(word,"on")))
   return 1; 
  else 
   {
    if ((ch=='N') || (ch=='F') || (ch=='0') || (!strcasecmp(word,"off")))
     return 0;
    else
     { printf("Bad boolean value '%s'.\n", word);  return -1; }
   }
}


/* Accept time value, and/or convert units to Seconds. Return 1 on success, 0 on failure. */
int accept_time( char *wrd, float *t )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",t)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strncasecmp(tval,"min",3)==0)  *t = 60.0 * *t;  else
 if (strncasecmp(tval,"hr",2)==0)  *t = 3600.0 * *t;  else
 if (strncasecmp(tval,"hour",4)==0)  *t = 3600.0 * *t;  else
 if (strncasecmp(tval,"day",3)==0)  *t = 24.0 * 3600.0 * *t;  else
 if ((strlen(tval)!=0) && (strncasecmp(tval,"sec",3)!=0)) { printf("Bad time unit %s.\n",tval); return 0; }
 return 1;
}


/* Accept frequency, and/or convert units to Hz. Return 1 on success, 0 on failure. */
int accept_frequency( char *wrd, float *freq )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",freq)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strcasecmp(tval,"KHz")==0)  *freq = *freq * 1e3;  else
 if (strcasecmp(tval,"MHz")==0)  *freq = *freq * 1e6;  else
 if (strcasecmp(tval,"GHz")==0)  *freq = *freq * 1e9;  else
 if (strcasecmp(tval,"THz")==0)  *freq = *freq * 1e12;  else  
 if ((strlen(tval)!=0) && (strcasecmp(tval,"Hz")!=0)) { printf("Bad frequency unit %s.\n",tval); return 0; } 
 return 1;
}


/* Accept temperature value, and convert units to degrees Celsius.  Returns 1 on success, 0 on failure. */
/* If no unit is specified, assumes degrees Celsius.  Otherwise expects "C[elsius]", "F[ahrenheit]",	*/
/* "K[elvin]", or "degrees C[elsius]", "degrees F[ahrenheit]", or "degrees K[elvin]".			*/
int accept_temperature( char *wrd, float *t )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",t)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strncasecmp(tval,"deg",3)==0) Xml_Next_Word( wrd, tval, " \t");
 if (strncasecmp(tval,"F",1)==0)  *t = (*t - 32.0) * (5.0/9.0);  else
 if (strncasecmp(tval,"K",1)==0)  *t = *t - 273.15;  else
 if ((strlen(tval)!=0) && (strncasecmp(tval,"C",1)!=0))
  { printf("Bad temperature unit %s.\n",tval); return 0; }
 return 1;
}


/* Accept power value, and/or convert units to Watts. Return 1 on success, 0 on failure. */
int accept_power( char *wrd, float *pwr )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",pwr)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strncasecmp(tval,"Kw",2)==0)  *pwr = *pwr * 1e3;  else
 if (strncasecmp(tval,"Mw",2)==0)  *pwr = *pwr * 1e6;  else 
 if ((strlen(tval)!=0) && (strncasecmp(tval,"watt",4)!=0)) { printf("Bad power unit %s.\n",tval); return 0; }
 return 1;
}


/* Accept DeciBells value, and/or convert units to linear. Return 1 on success, 0 on failure. */
int accept_dbvalue( char *wrd, float *value, char units )
{
 char tval[50];
 Xml_Next_Word( wrd, tval, " \t");  
 if (sscanf(tval,"%f",value)!=1) { printf("Bad float %s.\n",tval);  return 0; }
 Xml_Next_Word( wrd, tval, " \t");
 if (strcasecmp(tval,"dB")==0) 
 {
   switch (units)
    {
     case 'E':  *value = exp10( 0.1 * *value);  break;  /* Energy. */
     case 'P':  *value = exp10( 0.05 * *value); break;  /* Power. */
     default: printf("Bad dBs unit %s.\n",tval); return 0;  break;
    }
  }
 return 1;
}


