class Solution {
    public int longestValidParentheses(String s) {
        int len=s.length();
        if(len==0)
            return 0;
        int i=0,max=0;
        Stack<Integer> stack=new Stack();
        stack.push(-1);
        while(i<len){
            if(s.charAt(i)=='('){
                stack.push(i);
                
            }else{
                stack.pop();
                if(stack.empty()){
                    stack.push(i);
                }else{
                    max=max>(i-stack.peek())?max:(i-stack.peek());
                }
            }
            i++;
        }
        return max;
    }
}
