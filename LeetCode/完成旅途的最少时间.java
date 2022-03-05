class Solution {
    public long minimumTime(int[] time, int totalTrips) {
        long l=1,r=totalTrips;
        Arrays.sort(time);
        l=time[0];
        r=l*totalTrips;
        while(l<=r){
            long sum=0,ans=(l+r)>>1;
            for(int t:time){
                sum+=ans/t;
            }
            if(sum>=totalTrips)r=ans-1;
            else l=ans+1;
        }
        return l;
    }
}
