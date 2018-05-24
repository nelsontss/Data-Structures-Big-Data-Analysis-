
/**
 * Write a description of class GestStackOverflowMVCApp here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class GestStackOverflowMVCApp
{
    private static GestStackOverflowModel createDate(){
        GestStackOverflowModel e = new GestStackOverflowModel();
        Parser p = new Parser(e);
        p.parseUsers("");
        p.parsePosts("");
        p.parseTags("");
    }
    
    public static void main(String[] args){
        GestStackOverflowModel model = createDate();
        
    }
}
