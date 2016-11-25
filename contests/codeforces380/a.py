n = int(raw_input())

s = raw_input()

if n < 3:
	print s
	exit()

l = []

i = 0
flag2 = False
while i < n:

	if s[i] == 'o':
		flag2 = True
		starter = i
		i += 1
		if i < n and s[i] == 'g':
			i += 1
			if i < n and s[i] == 'o':
				i += 1
				flag = False
				flag2 = False
				while i < n:

					if s[i] == 'g' and not flag:
						flag = True
					elif s[i] == 'o' and flag:
						flag = False
					else:
						flag2 = True
						break
					i += 1

				if starter != -1 and i - starter >= 3:
					l.append(starter)
					if s[i-1] == 'g':
						l.append(i-2)
					else:
						l.append(i-1)
			else:
				starter = -1
		else:
			starter = -1

	else:
		starter = -1

	if flag2:
		i -= 1
		flag2 = False 
	i += 1

i = 0
j = 0
ans = ''
while i < n:
	if j+1 < len(l) and i == l[j]:
		ans += '***'
		i += l[j+1] - l[j] + 1
		j += 2

	else:
		ans += s[i]
		i += 1

print ans

