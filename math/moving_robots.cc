#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
using ll = int64_t;
using ld = double;
using mat = vector<vector<ld>>;

mat mat_mul(const mat& A, const mat& B) {
  mat C(A.size(), vector<ld>(B[0].size(), 0.0));
  for (ll i = 0; i < (ll) A.size(); i++) {
    for (ll j = 0; j < (ll) A[0].size(); j++) {
      for (ll k = 0; k < (ll) B[0].size(); k++) {
        C[i][k] += A[i][j] * B[j][k]; 
      }
    }
  }
  return C;
}

mat mat_pow(const mat& A, ll e) {
  if (e == 1) { return A; }
  else if (e % 2 == 0) { return mat_pow(mat_mul(A,A), e/2); }
  else { return mat_mul(A, mat_pow(A, e-1)); }
}

int main() {
  ll N = 8;
  ll NN = 8*8;
  vector<ll> DR = {-1, 0, 1, 0};
  vector<ll> DC = {0, 1, 0, -1};
  mat P(NN, vector<ld>(NN, 0.0));
  for (ll r = 0; r < N; r++) {
    for (ll c = 0; c < N; c++) {
      vector<ll> NBR;
      for (ll d = 0; d < 4; d++) {
        ll rr = r+DR[d];
	ll cc = c+DC[d];
	if (0 <= rr && rr < N && 0 <= cc && cc < N) {
	  NBR.push_back(rr*N+cc);
	}
      }
      for (ll y: NBR) {
        P[r*N+c][y] = 1.0 / static_cast<ld>(NBR.size());
      }
    }
  }

  ll k;
  cin >> k;
  mat Pk = mat_pow(P, k);
  
  ld ans = 0.0;
  for (ll rc = 0; rc < NN; rc++) {
    ld pempty = 1.0;
    for (ll ab = 0; ab < NN; ab++) {
      pempty *= 1.0 - Pk[ab][rc];
    }
    ans += pempty;
  }
  cout << fixed << setprecision(6) << ans << endl;
}
