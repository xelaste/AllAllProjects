import React from 'react';
import {formValues,Field, reduxForm } from 'redux-form';
/*

*/
const GameForm = props => {
    const { error, handleSubmit } = props;
    const digit = (value ,previousValue ,allValues ,previousAllValues) => 
    { 
        let prev = [previousAllValues.d1, previousAllValues.d2,previousAllValues.d3,previousAllValues.d4];
        let curr = [allValues.d1, allValues.d2,allValues.d3,allValues.d4];
        for (let i=0;i<curr.length;i++)
        {
            for (let j=0;j<prev.length;j++)    
            {
                if (i!=j && curr[i] && prev[j] && curr[i] == prev[j])
                {
                    return "";
                }
            }
        }
        return "123456789".includes(value)?value:""
    };
    function onChange(event, newValue, previousValue, name)
    {
        if ("123456789".includes(newValue) && newValue.length>0)
        {
            let x = parseInt(name.substring(2, 1)) % 4 + 1;
            document.getElementsByName("d" + x)[0].focus();
        }
    }
    let showSecret = props.vsComputer ||  props.isWin || props.isLost
    return (
        <div className="w-100">
            {showSecret && <h4 className="text-center">Secret: {props.secret}</h4>}
            {!showSecret && <h4 className="text-center">Enter Number</h4>}
            <form onSubmit={handleSubmit} className="form-horizontal">
                {error && <div className="mt-10 px-0 col-sm-6 alert alert-danger">{error}</div>}
                {!showSecret &&
                <div className="form-row w-100" style={{justifyContent:'center'}}>
                    <span className="digitSpan mr-1">
                        <Field
                            name="d1"
                            component="input"
                            type="text"
                            maxLength="1"
                            className="form-control form-control-sm"
                            normalize={digit}
                            onChange={onChange}
                            forwardRef="true"
                        />
                    </span>
                    <span className="digitSpan mr-1">
                        <Field
                            name="d2"
                            component="input"
                            type="text"
                            maxLength="1"
                            className="form-control form-control-sm"
                            normalize={digit}
                            onChange={onChange}
                        />
                    </span>
                    <span className="digitSpan mr-1">
                        <Field
                            name="d3"
                            component="input"
                            type="text"
                            maxLength="1"
                            className="form-control form-control-sm"
                            normalize={digit}
                            onChange={onChange}
                        />
                    </span>
                    <span className="digitSpan mr-1">
                        <Field
                            name="d4"
                            component="input"
                            type="text"
                            maxLength="1"
                            pattern="[1-9]{1}"
                            className="form-control form-control-sm"
                            normalize={digit}
                            onChange={onChange}
                        />
                    </span>
                </div>
                }
                {
                    props.vsComputer &&
                    <div className="overflow-auto" style={{ 
                        height: "40vh",
                        backgroundColor: "DeepPink" }}>
                        {
                            props.heap.map((x,i)=><span>{i > 0 && i % 6==0 && <br/>}{x}&nbsp;</span> )                                 
                        }
                    </div>   
                }
            </form>
        </div>
    );
};
export default reduxForm({
    form: 'gameForm', // a unique identifier for this form
})(GameForm);
