// template.cpp : Defines the entry point for the console application.
//
#include <climits>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <list>
#include <tuple>
#include <ctime>
#include <cassert>
using namespace std;


//type shortcuts
typedef long long ll;
typedef vector<ll> VI;
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;


//constants
const DOUBLE EPS=1e-9;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

ll divceil(ll x, ll y) {
    return (x + y - 1) / y;
}

ll simulate(ll hd, ll ad, ll hk, ll ak, ll b, ll d, ll bn, ll dn) {
    ll ret = 0;
    ll cap = hd;
    char last_action = 0;

    while (true) {
        assert(hd >= 1);
        assert(hk >= 1);
        ++ret;

        //dragon's move
        char exp_todo = (dn>0) ? 'd' : (bn>0) ? 'b' : 'a';
        bool exp_knight_live = (exp_todo == 'a') ? (ad<hk) : true;
        ll exp_knight_atk = (exp_todo == 'd') ? max(ak - d, (ll)0) : ak;
        bool exp_dragon_death = exp_knight_live&&hd <= exp_knight_atk;
        if (exp_dragon_death) {
            if (last_action == 'c') return -1;
            hd = cap;
            last_action = 'c';
        }
        else {
            switch (exp_todo) {
            case 'a':
                hk = max((ll)0, hk - ad);
                if (hk == 0) return ret;
                break;
            case 'b':
                ad += b;
                --bn;
                break;
            case 'd':
                ak = max(ak - d, (ll)0);
                --dn;
                break;
            }
            last_action = exp_todo;
        }

        //knight's move
        hd = max(hd - ak, (ll)0);
        if (hd == 0) {
            return -1;
        }
    }
}

ll solve(ll hd, ll ad, ll hk, ll ak, ll b, ll d) {
    ll ans = -1;
    ll dlimit = (d == 0) ? 0 : divceil(ak, d);
    ll blimit = (b == 0) ? 0 : divceil(max(hk - ad, (ll)0), b);
    rng(dn, 0, dlimit + 1) {
        rng(bn, 0, blimit + 1) {
            ll res = simulate(hd, ad, hk, ak, b, d, bn, dn);
            if (res<0) continue;
            ans = (ans<0 || res<ans) ? res : ans;
        }
    }
    return ans;
}

struct GameState {
    ll days;
    ll cap;
    ll hd;
    ll ad;
    ll hk;
    ll ak;
};

ll estimate(GameState &st, ll bat) {
    if (st.ak == 0) {
        return st.days + bat;
    }
    ll mxjdbks = divceil(st.cap, st.ak);//man xue ji dao bei kan si?
    ll dqjdbks = divceil(st.hd, st.ak);//dang qian ji dao bei kan si?
    if (mxjdbks == 1) {
        //if dragon cannot kill knight with 1 shot, dragon with be killed.
        if (bat >= 2) return -1;
        return st.days + 1;
    }
    else if (mxjdbks == 2) {
        if (dqjdbks == 1) {
            if (bat >= 2) return -1;
            return st.days + 1;
        }
        else {//==2
            if (bat >= 3) return -1;
            return st.days + bat;
        }
    }
    else {
        ll cure0 = (bat <= dqjdbks - 1) ? 0 : 1;
        ll zushu = (cure0 == 0) ? -1 : (divceil(bat - (dqjdbks - 1) - 1, mxjdbks - 2));
        ll cure1 = (cure0 == 0) ? 0 : (zushu - 1);
        return st.days + bat + cure0 + cure1;
    }
    return 0;
}

bool perform_extra_debuffs(GameState &st, ll target, ll debuff_effect) {
    assert(target >= 1);
    ll mxjdbks = divceil(st.cap, st.ak);//man xue ji dao bei kan si?
    ll dqjdbks = divceil(st.hd, st.ak);//dang qian ji dao bei kan si?
    if (mxjdbks == 1) {
        if (target >= 2) return false;
        st.days++;
        st.ak = max((ll)0, st.ak - debuff_effect);
        st.hd -= st.ak;
        if (st.hd <= 0) return false;
        return true;
    }
    else if (mxjdbks == 2) {
        if (dqjdbks == 1) {
            if (target >= 2) return false;
            st.days++;
            st.ak = max((ll)0, st.ak - debuff_effect);
            st.hd -= st.ak;
            if (st.hd <= 0) return false;
            return true;
        }
        else {//==2
            if (target == 1) {
                st.days++;
                st.ak = max((ll)0, st.ak - debuff_effect);
                st.hd -= st.ak;
                return true;
            }
            else if (target == 2) {
                st.days++;
                st.ak = max((ll)0, st.ak - debuff_effect);
                st.hd -= st.ak;
                st.days++;
                st.ak = max((ll)0, st.ak - debuff_effect);
                st.hd -= st.ak;
                if (st.hd <= 0) return false;
                return true;
            }
            else {
                return false;
            }
        }
    }
    else {
        //1. perform target-1 debuffs.
        ll crtgt = target - 1;
        ll maxdebuffallowedbefore1stcure = dqjdbks - 1;
        ll tgt0 = min(crtgt, maxdebuffallowedbefore1stcure);
        ll tgt1 = crtgt - tgt0;

        //1.1 perform subtask1.
        st.days += tgt0;
        st.hd = st.hd - tgt0*st.ak + debuff_effect*(tgt0 + 1)*tgt0 / 2;
        st.ak = st.ak - tgt0*debuff_effect;

        //1.2 perform subtask2.
        ll pdlen = mxjdbks - 1;
        ll prds = tgt1 / (mxjdbks - 2);
        ll rmdr = tgt1 % (mxjdbks - 2);
        //1.2.1 finish periods
        if (prds >= 1) {
            st.days += prds*(mxjdbks - 1);
            st.ak -= (tgt1 - rmdr)*debuff_effect;
            ll thatatk = st.ak + debuff_effect*(pdlen - 1);
            st.hd = st.cap - thatatk*pdlen + debuff_effect*pdlen*(pdlen - 1) / 2;
        }

        //1.2.2 finish remainders.
        if (rmdr >= 1) {
            st.days++;
            st.hd = st.cap - st.ak;

            st.days += rmdr;
            st.hd = st.hd - rmdr*st.ak + debuff_effect*(rmdr + 1)*rmdr / 2;
            st.ak = st.ak - rmdr*debuff_effect;
        }

        //2. perform the last debuff.
        ll exp_ak = max((ll)0, st.ak - debuff_effect);
        ll exp_hd = st.hd - exp_ak;
        if (exp_hd <= 0) {//should cure first.
            st.days++;
            st.hd = st.cap - st.ak;
        }
        st.days++;
        st.ak = max((ll)0, st.ak - debuff_effect);
        st.hd -= st.ak;
        assert(st.hd >= 1);
        return true;

        ll cure0 = (target <= dqjdbks - 1) ? 0 : 1;
        ll zushu = (cure0 == 0) ? -1 : divceil(target - (dqjdbks - 1), mxjdbks - 2);
        ll cure1 = (cure0 == 0) ? 0 : (zushu - 1);
        st.days += target + cure0 + cure1;
        ll lasttarget = (cure0 == 0) ? target : ((target - dqjdbks) / (mxjdbks - 2) + 1);
        ll lastak = st.ak - debuff_effect*(target - lasttarget);
        ll lasthp = (cure0 == 0) ? st.hd : st.cap - lastak;
        assert(lasttarget >= 1);
        st.hd = lasthp - lastak*lasttarget + debuff_effect*(lasttarget + 1)*lasttarget / 2;
        st.ak = max((ll)0, st.ak - target*debuff_effect);
        return true;
    }
}

ll solve2(ll hd, ll ad, ll hk, ll ak, ll b, ll d) {
    ll buff_atk_optimal = divceil(hk, ad);
    rng(t, 1, 100000) {
        buff_atk_optimal = min(buff_atk_optimal, t + divceil(hk, (ad + t*b)));
    }

    VI bar;
    bar.push_back(0);
    ll bn = 1;
    if (d >= 1) {
        while (ak>d*bar[bn - 1]) {
            ll pjds = divceil(hd, ak - d*bar[bn - 1]);//previous ji dao si
            if (ak <= d*(bar[bn - 1] + 1)) {
                bar.push_back(bar[bn - 1] + 1);
            }
            else {
                ll tjds = max(divceil(hd, ak - d*bar[bn - 1] - d), pjds + 1);//target ji dao si
                ll newbar = (ak*(tjds - 1) - hd) / (d*(tjds - 1)) + 1;
                bar.push_back(newbar);
            }
            ++bn;
        }
    }

    GameState st;
    st.days = 0; st.cap = st.hd = hd; st.ad = ad; st.hk = hk; st.ak = ak;
    ll db = 0;
    ll ans = -1;
    ll bi = 0;
    while (true) {
        ll att = estimate(st, buff_atk_optimal);
        ans = (att>0 && (ans<0 || att<ans)) ? att : ans;
        if (bi == bn - 1) break;
        if (!perform_extra_debuffs(st, bar[bi + 1] - bar[bi], d)) break;
        ++bi;
    }
    return ans;
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll hd,ad,hk,ak,b,d;cin>>hd>>ad>>hk>>ak>>b>>d;
        ll ans=solve2(hd,ad,hk,ak,b,d);
        cout<<"Case #"<<(ti+1)<<": ";
        if (ans<0){
            cout<<"IMPOSSIBLE";
        }else{
            cout<<ans;
        }
        cout<<endl;
    }
    return 0;
}
