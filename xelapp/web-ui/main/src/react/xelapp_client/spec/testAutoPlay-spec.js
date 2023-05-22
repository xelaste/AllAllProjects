import AutoPlay from "../src/auto/autoplay"

describe('AutoPlay tests', function () {
    it('AutoPlay', function () {
        let autoPlay = new AutoPlay();
        console.log("$$$$" + autoPlay.getInitialSet().length);
        expect(autoPlay.getInitialSet()).toBeDefined();
        let respond = autoPlay.calculate([1,2,3,4],[1,2,3,4]);
        expect(respond.matches).toEqual(4)
        expect(respond.exist).toEqual(0)
        respond = autoPlay.calculate([1,2,3,4],[9,5,6,1]);
        expect(respond.matches).toEqual(0);
        expect(respond.exist).toEqual(1)
        autoPlay.game([1,2,3,4]);
        autoPlay.game([5,2,6,9]);
    });
});
