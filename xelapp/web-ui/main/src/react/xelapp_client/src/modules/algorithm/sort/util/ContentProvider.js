export let content = Array.from({ length: 100 }, (_, i) => i+1)
export function shuffle(arr)
{
    for (let i=0;i <content.length;i++)
    {
        let idx =  Math.floor(Math.random() * i);
        let val = arr[idx];
        arr[idx]=arr[i];
        arr[i]=val;
    }
    return arr;
}
