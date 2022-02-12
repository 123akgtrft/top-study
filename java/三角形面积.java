public class N001 {
    public static void main(String[] args){
        Scanner input=new Scanner(System.in);
        System.out.println("Input coordination of triangle(x1 y1 x2 y2 x3 y3):");
        double x1,x2,x3,y1,y2,y3,a,b,c,A,area;
        x1=input.nextInt();
        y1=input.nextInt();
        x2=input.nextInt();
        y2=input.nextInt();
        x3=input.nextInt();
        y3=input.nextInt();
        a=Math.pow(Math.pow(x2-x3,2)+Math.pow(y2-y3,2),0.5);
        b=Math.pow(Math.pow(x1-x3,2)+Math.pow(y1-y3,2),0.5);
        c=Math.pow(Math.pow(x2-x1,2)+Math.pow(y2-y1,2),0.5);
        A=(b*b+c*c-a*a)/(2*b*c);
        A=Math.acos(A);
        area=0.5*b*c*Math.sin(A);
        System.out.printf("The triangle's area is %d",Math.round(area));
    }
}
