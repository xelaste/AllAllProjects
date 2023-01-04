export function generateSecretNumber()
{
    let secret = generateSecretArray()
    return secret.reduce((a,b)=>a * 10 + b);
}

export function generateSecretString()
{
    let secret = generateSecretArray()
    return secret.reduce((a,b)=>'' + a + b);
}

export function generateSecretArray()
{
    let secret = [0,0,0,0];
    let digits=[1,2,3,4,5,6,7,8,9]
    secret = secret.map((n)=>{
        let idx = Math.floor(Math.random() * 10) % digits.length;
        let digit= digits[idx]; 
        digits=digits.filter(x=>x!==digit);
        return digit;
    });
    return secret;
}