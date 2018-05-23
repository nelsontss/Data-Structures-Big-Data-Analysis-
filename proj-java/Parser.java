import java.io.FileInputStream;
import java.io.FileNotFoundException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class Parser {
   public Parser(){
       super();
   }
    //dwafqwfq
   public GestStackOverflowModel parse(String path) throws SAXException, FileNotFoundException {
       
         FileInputStream inputFile = new FileInputStream(path+"Users.xml");
         SAXParserFactory factory = SAXParserFactory.newInstance();
         SAXParser saxParser = factory.newSAXParser();
         GestStackOverflowModel e = new GestStackOverflowModel();
         
         UserHandler userhandler = new UserHandler(e);
         saxParser.parse(inputFile, userhandler); 
         
         inputFile = new FileInputStream(path+"Posts.xml"); 
         PostHandler posthandler = new PostHandler(e);
         saxParser.parse(inputFile, posthandler);     
      
         inputFile = new FileInputStream(path+"Posts.xml"); 
         TagsHandler tagshandler = new TagsHandler(e);
         saxParser.parse(inputFile, tagshandler);
         
         return e;
   }   
}

