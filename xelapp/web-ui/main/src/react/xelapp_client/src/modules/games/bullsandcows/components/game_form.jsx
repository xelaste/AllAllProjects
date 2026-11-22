import { useForm } from 'react-hook-form';

/*

*/
export const GameForm = props => {
    const { error: error, handleSubmit: onFormSubmit } = props;
    const { register, handleSubmit } = useForm({ mode: "onChange" });
    
    const validDigit = (input) => 
    { 
        let curr = [document.getElementsByName("d1")[0].value, 
                    document.getElementsByName("d2")[0].value,
                    document.getElementsByName("d3")[0].value,
                    document.getElementsByName("d4")[0].value
                ];

        let newValue = input.value;
        for (let i=0;i<curr.length;i++) {
            if (input===document.getElementsByName("d" + (i + 1) )[0]) {
                continue;
            }
            let value = document.getElementsByName("d" + (i + 1) )[0].value
            if ("123456789".includes(newValue) && newValue.length>0 && newValue===value) {
                input.value="";
                return false;
            }
        }
        return true;
    };
    function onChange(event)
    {
        let newValue = event.target.value;
        if ("123456789".includes(newValue) && newValue.length>0 && validDigit(event.target))
        {
            let x = parseInt(event.target.name.substring(2, 1)) % 4 + 1;
            document.getElementsByName("d" + x)[0].focus();
        }
        let curr = [ document.getElementsByName("d1")[0].value, 
                     document.getElementsByName("d2")[0].value,
                     document.getElementsByName("d3")[0].value,
                     document.getElementsByName("d4")[0].value
                ];

        props.handleDigitsChanged(curr);
    }
    let showSecret = props.vsComputer ||  props.isWin || props.isLost
    function reset () {
        if (!props.vsComputer) {
           document.getElementsByName("d1")[0].value="", 
           document.getElementsByName("d2")[0].value="",
           document.getElementsByName("d3")[0].value="",
           document.getElementsByName("d4")[0].value=""
        }
    }
    props.subscribeToGameForm (reset);
    return (
        <div className="w-100  text-dark">
            {showSecret && <h4 className="text-center">Secret: {props.secret}</h4>}
            {!showSecret && <h4 className="text-center">Enter Number</h4>}
            <form onSubmit={handleSubmit(onFormSubmit)} className="form-horizontal">
                {error && <div className="mt-10 px-0 col-sm-6 alert alert-danger">{error}</div>}
                {!showSecret &&
                <div className="form-row w-100" style={{justifyContent:'center'}}>
                    {[1, 2, 3, 4].map(i => (
                    <span key={i} className="digitSpan mr-1">
                        <input
                            name={`d${i}`}
                            type="text"
                            maxLength="1"
                            className="form-control form-control-sm"
                            onChange={onChange}
                        />
                    </span>
                    ))}
                </div>
                }
                {
                    props.vsComputer &&
                    <div className="overflow-auto  text-dark" style={{ 
                        height: "40vh",
                        backgroundColor: "DeepPink" }}>
                        {
                            props.heap.map((x,i)=><span key={'heap_itm_' + i}>{i > 0 && i % 6===0 && <br/>}{x}&nbsp;</span> )                                 
                        }
                    </div>   
                }
            </form>
        </div>
    );
};
