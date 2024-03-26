def bubble_sort(list):
    for i in range(0,len(list)-1):
        for j in range(i+1,len(list)):
            if list[i]<=list[j]:
                list[i],list[j] = list[j],list[i]
list = [1,5,4,3,6,3,7,3,8,10]
print(list)
bubble_sort(list)
for i in list:
    print(i,end=' ')
