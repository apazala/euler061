#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int v;
	struct tree *left;
	struct tree *right;
} tree;

tree *newtree(int v) {
	tree *newt = (tree *)calloc(1, sizeof(tree));
	newt->v = v;
	return newt;
}

tree *insert(tree *root, int v) {
	if (!root) {
		root = newtree(v);
	}
	else if (root->v > v) {
		root->left = insert(root->left, v);
	}
	else if (root->v < v) {
		root->right = insert(root->right, v);
	}

	return root;
}

void printtree(tree *root) {
	if (!root) return;
	printtree(root->left);
	printf("%d\n", root->v);
	printtree(root->right);
}

int low_bound(int value, int arr[], int n) {
	int low = 0;
	int high = n - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) >> 1;
		if (arr[mid] >= value)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

int triang[] = { 1035, 1081, 1128, 1176, 1225, 1275, 1326, 1378, 1431, 1485, 1540, 1596, 1653, 1711, 1770, 1830, 1891, 1953, 2016, 2080, 2145, 2211, 2278, 2346, 2415, 2485, 2556, 2628, 2701, 2775, 2850, 2926, 3003, 3081, 3160, 3240, 3321, 3403, 3486, 3570, 3655, 3741, 3828, 3916, 4005, 4095, 4186, 4278, 4371, 4465, 4560, 4656, 4753, 4851, 4950, 5050, 5151, 5253, 5356, 5460, 5565, 5671, 5778, 5886, 5995, 6105, 6216, 6328, 6441, 6555, 6670, 6786, 6903, 7021, 7140, 7260, 7381, 7503, 7626, 7750, 7875, 8001, 8128, 8256, 8385, 8515, 8646, 8778, 8911, 9045, 9180, 9316, 9453, 9591, 9730, 9870 };
int squar[] = { 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969, 4096, 4225, 4356, 4489, 4624, 4761, 4900, 5041, 5184, 5329, 5476, 5625, 5776, 5929, 6084, 6241, 6400, 6561, 6724, 6889, 7056, 7225, 7396, 7569, 7744, 7921, 8100, 8281, 8464, 8649, 8836, 9025, 9216, 9409, 9604, 9801 };
int pent[] = { 1001, 1080, 1162, 1247, 1335, 1426, 1520, 1617, 1717, 1820, 1926, 2035, 2147, 2262, 2380, 2501, 2625, 2752, 2882, 3015, 3151, 3290, 3432, 3577, 3725, 3876, 4030, 4187, 4347, 4510, 4676, 4845, 5017, 5192, 5370, 5551, 5735, 5922, 6112, 6305, 6501, 6700, 6902, 7107, 7315, 7526, 7740, 7957, 8177, 8400, 8626, 8855, 9087, 9322, 9560, 9801 };
int hexag[] = { 1035, 1128, 1225, 1326, 1431, 1540, 1653, 1770, 1891, 2016, 2145, 2278, 2415, 2556, 2701, 2850, 3003, 3160, 3321, 3486, 3655, 3828, 4005, 4186, 4371, 4560, 4753, 4950, 5151, 5356, 5565, 5778, 5995, 6216, 6441, 6670, 6903, 7140, 7381, 7626, 7875, 8128, 8385, 8646, 8911, 9180, 9453, 9730 };
int heptag[] = { 1071, 1177, 1288, 1404, 1525, 1651, 1782, 1918, 2059, 2205, 2356, 2512, 2673, 2839, 3010, 3186, 3367, 3553, 3744, 3940, 4141, 4347, 4558, 4774, 4995, 5221, 5452, 5688, 5929, 6175, 6426, 6682, 6943, 7209, 7480, 7756, 8037, 8323, 8614, 8910, 9211, 9517, 9828 };
int octog[] = { 1045, 1160, 1281, 1408, 1541, 1680, 1825, 1976, 2133, 2296, 2465, 2640, 2821, 3008, 3201, 3400, 3605, 3816, 4033, 4256, 4485, 4720, 4961, 5208, 5461, 5720, 5985, 6256, 6533, 6816, 7105, 7400, 7701, 8008, 8321, 8640, 8965, 9296, 9633, 9976 };

int sizes[] = { 0, 0, 0, sizeof(triang)/sizeof(int), sizeof(squar) / sizeof(int), sizeof(pent) / sizeof(int), sizeof(hexag) / sizeof(int), sizeof(heptag) / sizeof(int), sizeof(octog) / sizeof(int) };

int *polygon[] = { 0, 0, 0, triang, squar, pent, hexag, heptag, octog };


tree *solutions = NULL;
int *polytest[6];
int sizetest[6];
int t;

int chain[6];

void solve(int depth, int signature) {
	if (depth == t) {
		int sum = 0;
		for (int i = 0; i < depth; i++)
			sum += chain[i];
		solutions = insert(solutions, sum);
		return;
	}

	int v = 100 * (chain[depth - 1] % 100);
	int vlimit = v + 100;
	for (int i = 1; i < t; i++) {
		if ((1 << i) & signature) continue;


		int j = low_bound(v, polytest[i], sizetest[i]);
		for (int vlink = polytest[i][j]; vlink < vlimit; vlink = polytest[i][++j]) {

			//check valid
			int valid = 1;
			for (int z = 0; valid && z < depth; z++) {
				valid = (vlink != chain[z]);
			}
			if (!valid) continue;

			if (depth == t - 1) {//last
				int kk = chain[0] - 100 * (vlink % 100);
				valid =(kk > 0 && kk < 100);
			}
			if (!valid) continue;

			chain[depth] = vlink;
			solve(depth + 1, (1 << i) | signature);
		}

	}
}

int main()
{
    //Original problem input: 
    //6
    //3 4 5 6 7 8
	scanf("%d", &t); 
	for (int i = 0; i < t; i++) {
		int v;
		scanf("%d", &v);
		polytest[i] = polygon[v];
		sizetest[i] = sizes[v];
	}

	int sz = sizetest[0];
	for (int i = 0; i < sz; i++) {
		int bum = polytest[0][i];
		chain[0] = bum;
		solve(1, 1);
	}

	printtree(solutions);

    return 0;
}
