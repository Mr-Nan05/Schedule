#include "date.h"

Date::Date()
{
    today = QDate::currentDate();
}

Date::Date(QDate date)
{
    today = date;
}

QDate Date::get_lunar()
{
    solar_lunar(today.year(),today.month(),today.day());
    return QDate(lunar_year,lunar_month,lunar_day);
}

//确定是否存在农历的闰月 并返回闰月
unsigned char Date::get_leap_month(unsigned int lunar_year)
{
return lunar_info[lunar_year-1900]&0xf;
}

//若存在闰月,返回闰月的天数,30?29
unsigned char Date::get_leap_month_day(unsigned int lunar_year)
{
if(get_leap_month(lunar_year))
return( ( (lunar_info[lunar_year-1900]) & 0x10000 ) ? 30:29 );
else
return(0);
}
//确定农历当月天数,30?29
unsigned char Date::get_lunar_month_total(unsigned int lunar_year, unsigned char lunar_month)
{
return( (lunar_info[lunar_year-1900] & (0x10000>>lunar_month) ) ? 30:29 );
}
// 农历当年总天数,354?355 384 383
unsigned int Date::get_lunar_year_total(unsigned int lunar_year)
{
//12个月 29天一月
unsigned int sum=348;
unsigned int i;
for(i=0x8000;i>0x8; i>>=1)
sum+=(lunar_info[lunar_year-1900]&i)?1:0; //把大月的1加进去
return(sum+get_leap_month_day(lunar_year)); //判断这年是否有闰月
}


//判断是否为闰年
unsigned int Date::leap(unsigned int year)
{
if( (year%4==0 &&year%100!=0) || year%400==0 )
return 366;
else
return 365;
}

//判断当年当月天数
unsigned char Date::day(unsigned int year ,unsigned char month)
{
if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
return 31;
if(month==4||month==6||month==9||month==11)
return 30;
if(month==2&&leap(year)==366)
return 29;
else
return 28;
}

//计算1900.1.1 到 输入年月的天数
unsigned int Date::get_solar_total(unsigned int solar_year, unsigned char solar_month)
{
unsigned int total;
unsigned int temp_num;
total=0;
for(temp_num=1900;temp_num<solar_year;temp_num++)
total+=leap(temp_num);
for(temp_num=1;temp_num<solar_month;temp_num++)
total+=day(solar_year,temp_num);
return total;
}


unsigned char Date::solar_lunar(unsigned int kp_year,unsigned char kp_month,unsigned char kp_day)
{
unsigned int total_day=0;
unsigned char run_yue_flag=0,run_yue=0,year_flag=0;

if(kp_year<1900 || kp_year>2050 || kp_month>12 || kp_month==0 || (kp_year==1900 && kp_month==1) )
return 0;
if(kp_day>day(kp_year,kp_month) || kp_day==0)
return 0;

total_day=get_solar_total( kp_year, kp_month)+kp_day-30;
lunar_year=1900;
while(total_day>385) //385大于一年 留出一年多的时间用于条件计算
{
total_day-=get_lunar_year_total(lunar_year); //
lunar_year++;
}
if(total_day>get_lunar_year_total(lunar_year)) //排除lunar_year有闰月的情况
{
total_day-=get_lunar_year_total(lunar_year);
lunar_year++;

}
run_yue=get_leap_month(lunar_year); //当前闰哪个月
if(run_yue)
run_yue_flag=1; //有闰月则一年为13个月
else
run_yue_flag=0; //没闰月则一年为12个月

if(total_day==0) //刚好一年
{
lunar_day=get_lunar_month_total(lunar_year,12);
lunar_month=12;
}
else
{
lunar_month=1;
while(lunar_month<=12)
{
if( run_yue_flag==1 && lunar_month==(run_yue+1) ) //闰月处理
{
if(total_day>get_leap_month_day(lunar_year))
{
total_day-=get_leap_month_day(lunar_year); //该年闰月天数

}
//lunar_month--;
run_yue_flag=0;
continue;

}
if( total_day> get_lunar_month_total(lunar_year,lunar_month ) )
{
total_day=total_day-get_lunar_month_total(lunar_year,lunar_month); //该年该月天数
lunar_month++;
}
else
{
lunar_day=total_day;
break;
}
}
}
return 0;
}
