import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.HashMap;
import java.time.LocalDate;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.XMLEvent;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.Attribute;
import javax.xml.namespace.QName;
public class Parser {
   private GestStackOverflowModel e;
    
   public Parser(){
       super();
       this.e = new GestStackOverflowModel();
   }
   
   public Parser(GestStackOverflowModel e){
       super();
       this.e = e;
   }
   
   public void parseUsers(String path) throws XMLStreamException, FileNotFoundException {
       
         XMLInputFactory factory = XMLInputFactory.newInstance();
         XMLEventReader eventReader =
         factory.createXMLEventReader(new FileReader("Users.xml"));

         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
               
            switch(event.getEventType()) {
               
               case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                 
                 String Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 int Reputation = Integer.parseInt(startElement.getAttributeByName(new QName("Reputation")).getValue());
                 String DisplayName =startElement.getAttributeByName(new QName("DisplayName")).getValue();
                 String AboutMe =startElement.getAttributeByName(new QName("AboutMe")).getValue();
                 this.e.addUser(new myUser(Id,DisplayName,AboutMe,0,0,0,Reputation,new ArrayList<MyPost>()));
               }
               break;
            }   
        }
        
        
   }
    
    
   public void parsePosts(String path) throws XMLStreamException, FileNotFoundException {
       
         XMLInputFactory factory = XMLInputFactory.newInstance();
         XMLEventReader eventReader =
         factory.createXMLEventReader(new FileReader("Posts.xml"));

         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
            
            switch(event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                  
                 String Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 String ownerUser = startElement.getAttributeByName(new QName("ownerUser")).getValue();
                 LocalDate data = LocalDate.parse(startElement.getAttributeByName(new QName("CreationDate")).getValue().substring(0,9));
                 int Type = Integer.parseInt(startElement.getAttributeByName(new QName("PostTypeId")).getValue());

                 if(Type == 1){
                        String Title = startElement.getAttributeByName(new QName("Title")).getValue();
                        int answerCount = Integer.parseInt(startElement.getAttributeByName(new QName("answerCount")).getValue());
                        String x = startElement.getAttributeByName(new QName("Tags")).getValue();
                        x = x.substring(1,x.length()-2);
                        String[] a = x.split("\\s*><\\s*");
                        ArrayList<String> Tags = new ArrayList<String>();
                        for(String s : a)
                        Tags.add(s);
                        this.e.addPost(new Pergunta(Title,Tags,new ArrayList<Resposta>(),new HashMap<String,Resposta>(),answerCount, Id, ownerUser,data));
                 }else{
                         String parentId = startElement.getAttributeByName(new QName("ParentId")).getValue();
                         int score = Integer.parseInt(startElement.getAttributeByName(new QName("Score")).getValue());
                         int comments = Integer.parseInt(startElement.getAttributeByName(new QName("commentsCount")).getValue());
                         this.e.addPost(new Resposta(parentId,comments,score,Id,ownerUser,data));
                  }
               }
               break;
           }
         
        }
        
        
   } 
    
    
   public void parseTags(String path) throws XMLStreamException, FileNotFoundException {
       
         XMLInputFactory factory = XMLInputFactory.newInstance();
         XMLEventReader eventReader =
         factory.createXMLEventReader(new FileReader("Tags.xml"));

         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
            
            switch(event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                 String Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 String Name = startElement.getAttributeByName(new QName("TagName")).getValue();
                 this.e.addTag(Name,Id);
               }
               break;
           }
         
        }
        
        
    }  
}