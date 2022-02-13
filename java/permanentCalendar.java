package Test1;

public class PrintCurrentTime {
    public static void main(String[] args){
        System.out.println(getYear()+" / "+getMonth(getYear())+" / "+getDay(getYear(),getMonth(getYear())));
        System.out.println(getHour()+" : "+getMinute()+" : "+getSecond());
    }
    public static long getTotalDay(){
        return Math.round((System.currentTimeMillis()/1000.0/60/60/24));
    }
    public static int getYear(){
        int year=1970,days=isLeapYear(1970)?366:365;
        long totalDay=getTotalDay();
        while(totalDay>days){
            totalDay-=days;
            year++;
            days=isLeapYear(year)?366:365;
        }
        return year;
    }
    public static int getMonth(int year){
        long totalDay=getTotalDay();
        int i,days=getNumberOfDaysMonth(year,1);
        for(i=1970;i<year;i++)
            totalDay-=isLeapYear(i)?366:365;
        i=1;
        while(totalDay>days){
            totalDay-=days;
            i++;
            days=getNumberOfDaysMonth(year,i);
        }
        return i;
    }
    public static int getDay(int year,int month){
        int i;
        long totalDay=getTotalDay();
        for(i=1970;i<year;i++)
            totalDay-=isLeapYear(i)?366:365;
        for(i=1;i<month;i++)
            totalDay-=getNumberOfDaysMonth(year,i);
        return (int)totalDay+1;
    }
    public static int getHour(){
        return (int)(System.currentTimeMillis()/1000/60/60+8)%24;
    }
    public static int getMinute(){
        return (int)(System.currentTimeMillis()/1000/60)%60;
    }
    public static int getSecond(){
        return (int)(System.currentTimeMillis()/1000)%60;
    }
    public  static int getNumberOfDaysMonth(int year,int month) {
        if (month == 1 || month == 3 || month == 5 || month == 8 || month == 7 || month == 10 || month == 12)
            return 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
        if(isLeapYear(year))
            return 29;
        else
            return 28;
    }
    public  static boolean isLeapYear(int year){
        return (year%400==0||(year%4==0&&year%100!=0));
    }
}

