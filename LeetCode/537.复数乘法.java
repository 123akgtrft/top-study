class Solution {
    public String complexNumberMultiply(String num1, String num2) {
        int len1=num1.length(),len2=num2.length();
        String[] str1=num1.split("\\+|i");
        String[] str2=num2.split("\\+|i");      
        int real1 = Integer.parseInt(str1[0]);
        int imag1 = Integer.parseInt(str1[1]);
        int real2 = Integer.parseInt(str2[0]);
        int imag2 = Integer.parseInt(str2[1]);
        return String.format("%d+%di",real1*real2-imag1*imag2,real1*imag2+real2*imag1);
    }
}
