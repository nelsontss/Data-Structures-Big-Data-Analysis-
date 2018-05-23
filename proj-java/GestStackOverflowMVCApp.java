
/**
 * Write a description of class GestStackOverflowMVCApp here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class GestStackOverflowMVCApp
{
    private static GestStackOverflowModel createDate(){
        Parser p = new Parser();
        return p.parse("");
    }
    
    public static void main(String[] args){
        GestStackOverflowModel model = createDate();
        
    }
}
