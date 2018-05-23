import java.util.HashMap;
import java.util.ArrayList;
import org.xml.sax.Attributes;
import java.time.LocalDate;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class TagsHandler extends DefaultHandler {
   private GestStackOverflowModel e;
    
   public TagsHandler(GestStackOverflowModel e){
       super();
       this.e = e;
   } 
  
   public void startElement(String uri, 
   String localName, String qName, Attributes attributes) throws SAXException {

      if (qName.equalsIgnoreCase("row")) {
         String Id = attributes.getValue("Id");
         String Name = attributes.getValue("TagName");
         this.e.addTag(Name,Id);
      }
   }  
   }