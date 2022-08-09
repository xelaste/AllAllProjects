class Vertex {
    id;
    data = {};
    attributes= {};
    constructor (id,data,attributes)
    {
        this.id=id;
        if (data) {
            this.data=data;
        } 
        if (attributes)
        {
            this.attributes=attributes;
        }    
    }
    getId()
    {
        return this.id;
    }
    getData (){
        return this.data;
    }
    getAttributes ()
    {
        return this.attributes;
    }
}
export default Vertex;