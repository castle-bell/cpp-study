
template <typename T>
T GetMax(T T1, T T2)
{
	return T1 > T2 ? T1 : T2;
}

int main()
{
	auto max1 = GetMax(1, 2);
	auto max2 = GetMax(1.0f, 2.0f);
	return 0;
}