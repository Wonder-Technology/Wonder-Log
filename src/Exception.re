exception Check_fail(string);

let throw = [%bs.raw {|
    function(msg){
            throw new Error(msg)
    }|}];