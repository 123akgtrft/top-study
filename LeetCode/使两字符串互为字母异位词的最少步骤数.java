class Solution {
    public int minSteps(String s, String t) {
        int[] a=new int[26],b=new int[26];
        for(char ch:s.toCharArray())
            a[ch-'a']++;
        for(char ch:t.toCharArray())
            b[ch-'a']++;
        int ans=0;
        for(int i=0;i<26;i++){
            if(a[i]==b[i])continue;
            ans+=Math.abs(a[i]-b[i]);
        }
        return ans;
    }
}
