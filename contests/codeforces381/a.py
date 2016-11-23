n, a, b, c = map(int, raw_input().split())

ans = 0

qt = n % 4

if qt == 0:
	print 0
	exit()

elif qt == 1:
	ans += min([3*a, a + b, c, a + 3*b])

elif qt == 2:
	ans += min([2*a, 3*c+a, b, 2*c])

else:
	ans += min([a, b+c, 2*c+b, 3*c])

print ans
