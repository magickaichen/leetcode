/*
Longest Consecutive Sequence

http://leetcode.com/onlinejudge#question_128

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/

//=======================================================================
// Longest Consecutive Sequence
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        // use hash table of smart structure to store the sequence {size}
        // for every number n
        // if n exist, do nothing
        // else if n-1 and n+1, sequence [?, n-1] and [n+1, ?] extend to [?, ?]
        // else if n-1 and no n+1, sequence [?, n-1] extend, update head and end of sequence [?, n-1] to [?, n] { size[?]++ }, { size[n] = size[?] }, and update max sequence size
        // else if no n-1 and n+1, sequence [n+1, ?] extend, update head and end of sequence [n+1, ?] to [n, ?] { size[?]++ }, { size[n] = size[?] }, and update max sequence size
        // else (no n-1 and no n+1), sequence [n, n], header {1}
        
        unordered_map<int, int> seq;  // number -> sequence size mapping
        int maxseq = 0;
        
        for(int i=0; i<num.size(); ++i) {
            if(seq.count(num[i]) == 0) {
                if(seq.count(num[i]-1) != 0) {
                    if(seq.count(num[i]+1) != 0) {
                        seq[num[i]] = seq[num[i]-1] + seq[num[i]+1] + 1;
                        // start and end of new sequence
                        seq[num[i] - seq[num[i]-1]] = seq[num[i]];
                        seq[num[i] + seq[num[i]+1]] = seq[num[i]];
                    } else {
                        seq[num[i]] = seq[num[i]-1] + 1;
                        // start of new sequence
                        seq[num[i] - seq[num[i]-1]] = seq[num[i]];
                    }
                } else {
                    if(seq.count(num[i]+1) != 0) {
                        seq[num[i]] = seq[num[i]+1] + 1;
                        // end of new sequence
                        seq[num[i] + seq[num[i]+1]] = seq[num[i]];
                    } else {
                        seq[num[i]] = 1;
                    }
                }
                if(seq[num[i]] > maxseq) 
                    maxseq = seq[num[i]];
            } // end of : if(seq.count(num[i]) == 0) {
        } // end of : for(int i=0; i<num.size(); ++i) {
        
        return maxseq;
    }
};