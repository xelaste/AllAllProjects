import React, { useState, useEffect, useCallback } from "react";
import "../../../../css/App.css";
import 'bootstrap/dist/css/bootstrap.min.css';
import SortLogicalView from "../view/SortLogicalView";
import {content as defaultContent,shuffle} from '../util/ContentProvider';
import {sleep} from '../../../../util/Sleep';
export default function Sorts(props) {
    const [loaded, setLoaded] = useState(false);
    const [execution, setExecution] = useState(false);
    const [state, setState] = useState({});
    let content=defaultContent;
    let swap = (i,j) =>
    {
        let tmp = content[i];
        content[i] = content[j];
        content[j] = tmp;
    }
    async function quickSortCall()
    {
        setExecution(true)
        await quickSort( 0 , content.length - 1);
        setExecution(false)
    }

    async function quickSort(from,to)
    {
        if (to-from===1)
        {
            if (content[to] < content[from]) {
               swap(to,from);
            }
            state.complexity+=5;
            let newState = {
                ...state
            }
            setState(newState);
            await sleep(30);           
            return;
        }
        if (  to + 1 - from < 3 ) {
            for (let i=from;i<=to;i++)
            {
                for (let j=i;j<to-i;j++)
                {
                    if (content[j]>content[j+1])
                    {
                        swap(j,j+1);
                    }
                    state.complexity+=7;
                    let newState = {
                        ...state
                    }
                    setState(newState);
                    await sleep(50);                   
                }
            }       
            return;
        }
        let pivot = Math.floor ((to+from)/2)
        let i = from;
        let j = to;
        let pivotIdx=-1;
        while (i<j && j>=0 && i<content.length) 
        {
            while (content[i]<pivot && i<content.length) {
                i++;
                state.complexity++;
                let newState = {
                    ...state
                }
                setState(newState);
                await sleep(30);               
            }
            while (content[j]>=pivot && j > i ) {
                if (content[j]===pivot)
                {
                    pivotIdx=j;
                }
                j--;
                state.complexity+=3;
                let newState = {
                    ...state
                }
                setState(newState);
                await sleep(30);               
            }
            if (i<j && content[i]>=pivot && content[j]<pivot)
            {
                swap(i,j);
            }
            state.complexity+=6;
            let newState = {
                ...state
            }
            setState(newState);
            await sleep(30);               
        }
        if ( pivotIdx >= 0 ) {
          swap (pivotIdx,i)  
        }
        state.complexity+=5;
        let newState = {
            ...state
        }
        setState(newState);
        await sleep(30);               

        if (j>=0) await quickSort(from,j);
        if (i<content.length) await quickSort(j+1,to);
    }

    async function mergeSortCall()
    {
        setExecution(true)
        await mergeSort( 0 , content.length - 1);
        setExecution(false)
    }
    async function mergeSort( from , to)
    {
        if (from===to)
        {
            state.complexity++;
            let newState = {
                ...state,
            }
            setState(newState);
            return [content[from]];
        }
        else if (from+1===to) {
            let arr = []
            arr[0] = content[from]<content[to]?content[from]:content[to]
            arr[1] = content[from]>=content[to]?content[from]:content[to]
            state.complexity+=5;
            let newState = {
                ...state
            }
            setState(newState);
            return arr;  
        }       
        let halfIdx = Math.floor((from + to)/2);
        let half1 = await mergeSort (from,halfIdx);
        let half2 = await mergeSort (halfIdx + 1 , to);
        let idx1=0
        let idx2=0
        state.complexity+=5;
        for (let i=0;i<half1.length + half2.length;i++)
        {
            let idx = i + from;
            if (idx1 < half1.length && idx2 < half2.length) {
                if (half1[idx1] < half2[idx2])
                {
                    content[idx]=half1[idx1]
                    idx1++;                        
                } 
                else
                {
                    content[idx]=half2[idx2];
                    idx2++;    
                }
            } else if (idx1 >= half1.length) {
                content[idx]=half2[idx2];
                idx2++;    
            } else {
                content[idx]=half1[idx1]
                idx1++;                        
            }
        
            state.complexity+=5;
            let newState = {
                ...state
            }
            setState(newState);
            await sleep(30);
        }
        return content.slice(from,to + 1);
    }

    async function selectSort()
    {
        setExecution (true);
        let complexity = 0;
        for (let i=0;i<content.length;i++)
        {
            complexity+=2;
            let max = 0;
            for (let j=0;j<content.length - i;j++)
            {
               complexity+=2;
               if (content[j] > content[max])
               {
                 max = j;
                 complexity+=3;
               }
               else {
                complexity++;
               }
            }
            let last = content.length - (i+1);
            swap(last,max);
            complexity+=4;
            let newState = {
                ...state,
                content:content,
                complexity:complexity
            }
            setState(newState);
            await sleep(300);
        }
        setExecution (false);
    }
    async function insertSort()
    {
        setExecution (true);
        let complexity=0;
        for (let i=1;i<content.length;i++)
        {
            complexity++;
            for (let j=i;j>0;j--)
            {
                complexity++;
                if (content[j]<content[j-1])
                {
                    swap(j-1,j);
                    complexity+=4;
                    let newState = {
                        ...state,
                        content:content,
                        complexity:complexity
                    }
                    setState(newState);
                    await sleep(30);
                }
                else {
                    complexity++
                }
            }
        }
        setExecution (false);
    }
    function onSortSelect (e) 
    { 
        let newState = {
            ...state,
            content:content,
            start:Math.floor(Date.now() / 1000),
            complexity:0,
            selectedSort:e.target.value
        }
        setState(newState);
    } 
    function isValidSort() {
      let selectedSort = state.selectedSort;
      return  selectedSort === "1" 
      ||
      selectedSort === "2"
      ||
      selectedSort === "3"
      ||
      selectedSort === "4"

    }

    function sort()
    {
        state.complexity=0;
        state.start=Math.floor(Date.now() / 1000);
        let newState = {
            ...state,
            complexity: 0,
            start: Math.floor(Date.now() / 1000),
            content:content
        }
        setState(newState);
        switch (state.selectedSort) { 
          case "1":
            selectSort();
            break;
          case "2":
            insertSort();
            break;
          case "3":
            mergeSortCall();
            break;
          case "4":
            quickSortCall();
            break;  
        }
    }

    function sortName()
    {
        let sortName = "Please Specify";
        switch (state.selectedSort) { 
          case "1":
            sortName = "Selection Sort"
            break;
          case "2":
            sortName = "Insertion Sort"
            break;
          case "3":
            sortName = "Merge Sort";
            break;
          case "4":
            sortName = "Quick Sort";
            break;  
        }
        return sortName;
    }
    useEffect(() => {
        if (!loaded) {
            setLoaded(true);
        }
    }, []);
    return <>
        <div className="home">
            <div className="container-fluid">
                <div className="row text-center">
                    <h3 className="display-4 text-primary">Sorts</h3>
                </div>
                <div className="row h-100">
                    <div className="col-3 display-6 text-primary">
                        <div className="card fs-6 mt-10 p-6 w-100 border-dark bg-secondary mb-3">
                            <div className="card-header  bg-dark">
                                <h3 className="text-white">Configuration</h3>
                            </div>
                            <div className="card-body">
                                <form>
                                    <label className="mb-1" htmlFor="sortTypesList">Sorting algorithms</label>
                                    <select defaultValue="Please Specify" disabled={execution} id="sortTypesList" onChange={onSortSelect} className="form-select form-label form-select-lg mb-3">
                                        <option value="Please Specify">Select Sort Algorithm</option>
                                        <option value="1">Selection Sort</option>
                                        <option value="2">Insertion Sort</option>
                                        <option value="3">Merge Sort</option>
                                        <option value="4">Quick Sort</option>
                                    </select>


                                    <button
                                        type="button"
                                        disabled={execution}
                                        style={{ width: "6em" }}
                                        onClick={(e)=>{
                                            shuffle(content);
                                            let newState = {
                                                ...state,
                                                complexity:0,
                                                start:Math.floor(Date.now() / 1000),
                                                content:content
                                            }
                                            setState(newState);
                                        }}
                                        className="btn btn-primary mt-2"
                                    >
                                        Shuffle
                                    </button>
                                    <button
                                        type="button"
                                        disabled={execution || !isValidSort()}
                                        style={{ width: "6em" }}
                                        onClick={(e)=>{
                                            sort();
                                        }}
                                        className="btn btn-primary mt-2 mx-2"
                                    >
                                        Run
                                    </button>
                                </form>
                            </div>
                        </div>
                        <div style={{ height: "38%" }} className="card fs-6  w-100 border-dark bg-info mb-3 overflow-auto">
                            <div className="card-header bg-primary">
                                {execution ? (
                                    <h3 className="bg-secondary blinking">Running</h3>
                                ) : (
                                    <h3 className="text-dark">Results</h3>
                                )}
                            </div>
                            <div className="card-body text-dark overflow-auto">
                                <div className="row row-eq-height align-items-end">
                                    <div className="col">
                                        <label>Input size</label>
                                        <span className="m-1">{content.length}</span>
                                    </div>
                                </div>
                                <div className="row row-eq-height align-items-end">
                                    <div className="col">
                                        <label>Complexity</label>
                                        <span className="m-1">{state.complexity}</span>
                                    </div>
                                </div>
                                <div className="row row-eq-height align-items-end">
                                    <div className="col">
                                        <label>Elapsed Time</label>
                                        <span className="m-1">{state.start?Math.floor(Date.now()/1000)-state.start:""}</span>
                                    </div>
                                </div>
                            </div>
                        </div>

                    </div>
                    <div className="col-9">
                        <div className="ps-2 me-1 fs-5 bg-secondary text-info">{sortName()}</div>
                        <div
                            id="algorithmContainer"
                            style={{ width: "100%", height: "80%" }}
                            className="overflow-auto"
                        >
                            <SortLogicalView progress={state.progress} title={state.selectedSort} content={content}></SortLogicalView>
                        </div>
                    </div>
                </div>
            </div>


        </div>
    </>
}