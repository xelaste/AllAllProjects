import {generateSecretArray,generateSecretString,generateSecretNumber} from '../src/util/secretGenerator';

describe('Generate Secret Tests', function() 
{
    it('Secret Array', function() 
    {
        let arr = generateSecretArray();
        console.log("######" + arr);
        expect(arr.length).toEqual(4);
        arr.forEach(element => {
            console.log("[" + element + "]");
            expect(element).toBeGreaterThan(0);
        });
    });
    it('Secret Number', function() 
    {
        let number = generateSecretNumber();
        console.log("$$$$" + number);
        expect(number).toBeGreaterThan(1000);
        expect(number).toBeLessThan(10000);
    });

    it('Secret String', function() 
    {
        let string = generateSecretString();
        console.log("@@@@" + string);
        expect(parseInt(string)).toBeGreaterThan(1000);
        expect(parseInt(string)).toBeLessThan(10000);
    });

});