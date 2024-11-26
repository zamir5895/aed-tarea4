#ifndef HW4_IMPL_H
#define HW4_IMPL_H

#include <string>
#include <vector>

#include "hw4.h"

std::vector<int> stringMatch_naive(const std::string& text, const std::string& pattern) {
    std::vector<int> ret; 

    int n = text.size();
    int m = pattern.size();

    if (m == 0 || n == 0 || m > n) {
        return ret;  
    }

    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;  
            }
        }
        if (match) {
            ret.push_back(i);  
        }
    }

    return ret;
}


std::vector<int> stringMatch_RabinKarp(const std::string& text, 
const std::string& pattern) {
    std::vector<int> ret; 

    int M = pattern.size(); 
    int N = text.size();    
    int d = 256;           
    int q = 101;            
    int h = 1;              
    int p = 0;              
    int t = 0;              

    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= N - M; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < M; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                ret.push_back(i); 
            }
        }

        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0) {
                t = (t + q);
            }
        }
    }

    return ret;
}




void construccion(const std::string& pattern, std::vector<int>& lps) {
    int len = 0; // Longitud del prefijo más largo
    int i = 1;   // Posición actual en el patrón
    lps[0] = 0;  // El primer valor de LPS siempre es 0

    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

std::vector<int> stringMatch_KnuthMorrisPratt(const std::string& text, const std::string& pattern) {
    std::vector<int> ret; 
    int n = text.size();  
    int m = pattern.size();

    if (m == 0 || n == 0 || m > n) {
        return ret; 
    }

    std::vector<int> lps(m, 0);
    construccion(pattern, lps);

    int i = 0; 
    int j = 0; 

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == m) { 
                ret.push_back(i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) {
                j = lps[j - 1]; 
            } else {
                i++; 
            }
        }
    }

    return ret;
}


#endif
