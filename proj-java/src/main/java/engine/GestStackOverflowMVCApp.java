package engine;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
/**
 * Write a description of class GestStackOverflowMVCApp here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class GestStackOverflowMVCApp
{
    private static GestStackOverflowModel createDate(String path) throws FileNotFoundException, XMLStreamException {
        GestStackOverflowModel estado = new GestStackOverflowModel();
        Parser p = new Parser(estado);
        
        p.parseUsers(path);
        p.parsePosts(path);
        p.parseTags(path);
        return estado;
        
        
        
    }
    
    public static void main(String[] args){
        
        GestStackOverflowModel model;
        try{
            model = createDate("xml/");
        }catch(FileNotFoundException e){
            System.out.println("Ficheiro nao encontrado!");
            return;
        }catch(XMLStreamException e){
             e.printStackTrace();
            return;
        }
        
        
        System.out.println(model.toString());
    }
}
