import java.util.HashMap;
import java.util.ArrayList;
import org.xml.sax.Attributes;
import java.time.LocalDate;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class PostHandler extends DefaultHandler {
   private GestStackOverflowModel e;
    
   public PostHandler(GestStackOverflowModel e){
       super();
       this.e = e;
   }
  
   public void startElement(String uri, 
   String localName, String qName, Attributes attributes) throws SAXException {

      if (qName.equalsIgnoreCase("row")) {
         String Id = attributes.getValue("Id");
         String ownerUser = attributes.getValue("ownerUser");
         LocalDate data = LocalDate.parse(attributes.getValue("CreationDate").substring(0,9));
         int Type = Integer.parseInt(attributes.getValue("PostTypeId"));
         
         if(Type == 1){
             String Title = attributes.getValue("Title");
             int answerCount = Integer.parseInt(attributes.getValue("answerCount"));
             String x = attributes.getValue("Tags");
             x = x.substring(1,x.length()-2);
             String[] a = x.split("\\s*><\\s*");
             ArrayList<String> Tags = new ArrayList<String>();
             for(String s : a)
                Tags.add(s);
             this.e.addPergunta(new Pergunta(Title,Tags,new ArrayList<Resposta>(),new HashMap<String,Resposta>(),answerCount, Id, ownerUser,data));
            }else{
             String parentId = attributes.getValue("ParentId");
             int score = Integer.parseInt(attributes.getValue("Score"));
             int comments = Integer.parseInt(attributes.getValue("Score"));
             this.e.addResposta(new Resposta());
            }

        }
      }  
   }
  
