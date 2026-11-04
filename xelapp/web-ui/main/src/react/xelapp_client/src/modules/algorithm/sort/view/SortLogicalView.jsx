import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../../controls/DrawPanel';
import {content as defaultContent,shuffle} from '../util/ContentProvider';
let margin=28
function SortLogicalView(props) {
    let handleResize = () => { };
    let content = props.content ? props.content : defaultContent;
    let progress = props.progress;
    if (!progress)
    {
        progress = {};
    }
    let getColor = (idx)=>{
        if (idx === progress.left ) {
            return '#1A5276'
        }
        if (idx === progress.right ) {
            return '#1A5276'
        }

        if (idx === progress.current ) {
            return "#4c516d";
        }

        if (idx === progress.max ) {
            return "#A93226";
        }        
        return "#00c0c0";

    }
    let drawContent = (_2dgraphics, data) => { 
        let selected = false;
        let width = data.range.width - margin;
        let height = data.range.height - margin 
        let color = (selected) ? "#4c516d" : "#00c0c0";
        _2dgraphics.beginPath();
        _2dgraphics.lineWidth = 2
        _2dgraphics.strokeStyle = color;
        _2dgraphics.fillStyle = color;
        _2dgraphics.moveTo(margin,height);
        _2dgraphics.lineTo(width  , height );
        _2dgraphics.stroke();
        _2dgraphics.closePath();
        let step = (width - margin)/content.length;
        let max = Math.max(...content);
        let min = Math.min (...content);
        for (let i=0;i<content.length;i++)
        {
            let val = ( max - content[i] ) / max - min;
            _2dgraphics.beginPath();
            _2dgraphics.lineWidth = 2
            _2dgraphics.strokeStyle = getColor(i);
            _2dgraphics.fillStyle = getColor(i);
            _2dgraphics.moveTo( ( margin + 5) + step * i ,height);
            _2dgraphics.lineTo( ( margin + 5) + step * i  , height + (height - margin )* val );
            _2dgraphics.stroke();
            _2dgraphics.closePath();
    
        }
    };

    return <>
        <DrawPanel drawContent={drawContent}
            handleContentResize={handleResize}
            containerId="algorithmContainer" title={props.title}></DrawPanel>
    </>
}
export default SortLogicalView;