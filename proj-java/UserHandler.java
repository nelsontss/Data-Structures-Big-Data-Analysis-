import java.util.HashMap;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class UserHandler extends DefaultHandler {
   private GestStackOverflowModel e;
    
   public UserHandler(GestStackOverflowModel e){
       super();
       this.e = new GestStackOverflowModel();
   }
  
   public void startElement(String uri, 
   String localName, String qName, Attributes attributes, GestStackOverflowModel e) throws SAXException {

      if (qName.equalsIgnoreCase("row")) {
         String Id = attributes.getValue("Id");
         int Reputation = Integer.parseInt(attributes.getValue("Reputation"));
         String DisplayName = attributes.getValue("DisplayName");
         String AboutMe = attributes.getValue("AboutMe");
         this.e.addUser(new myUser(Id,DisplayName,AboutMe,0,0,0,Reputation,new ArrayList<MyPost>()));
      }  
   }
   
}

