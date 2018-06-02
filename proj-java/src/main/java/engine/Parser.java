import java.io.FileNotFoundException;
import java.io.FileInputStream;
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
         factory.createXMLEventReader(new FileInputStream(path + "Users.xml"));
         
         String Id = "";
         int Reputation = 0;
         String DisplayName = "" ;
         String AboutMe = "";
         Attribute a ;
         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
               
            switch(event.getEventType()) {
               
               case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                 
                 Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 Reputation = Integer.parseInt(startElement.getAttributeByName(new QName("Reputation")).getValue());
                 DisplayName = startElement.getAttributeByName(new QName("DisplayName")).getValue();
                 a = startElement.getAttributeByName(new QName("AboutMe"));
                 if (a!=null)
                    AboutMe = a.getValue();
                 this.e.addUser(new myUser(Id,DisplayName,AboutMe,0,0,0,Reputation,new ArrayList<MyPost>()));
               }
               break;
            }   
        }
        
        
   }
    
    
   public void parsePosts(String path) throws XMLStreamException, FileNotFoundException {
       
         XMLInputFactory factory = XMLInputFactory.newInstance();
         XMLEventReader eventReader =
         factory.createXMLEventReader(new FileInputStream(path + "Posts.xml"));
         
         String Id = "";
         String ownerUser = ""; 
         LocalDate data = LocalDate.now();
         int Type = 0;

         
         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
            
            switch(event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                  
                 Attribute at;  
                 Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 //ownerUser = startElement.getAttributeByName(new QName("ownerUser")).getValue();
                 data = LocalDate.parse(startElement.getAttributeByName(new QName("CreationDate")).getValue().substring(0,10));
                 Type = Integer.parseInt(startElement.getAttributeByName(new QName("PostTypeId")).getValue());

                 if(Type == 1){
                        String Title = "";
                        int answerCount = 0;
                        String x = "";
                        
                        
                        Title = startElement.getAttributeByName(new QName("Title")).getValue();
                        at=startElement.getAttributeByName(new QName("AnswerCount"));
                        if(at!=null)
                            answerCount = Integer.parseInt(at.getValue());
                        x = startElement.getAttributeByName(new QName("Tags")).getValue();
                        x = x.substring(1,x.length()-2);
                        String[] a = x.split("\\s*><\\s*");
                        ArrayList<String> Tags = new ArrayList<String>();
                        for(String s : a)
                        Tags.add(s);
                        this.e.addPost(new Pergunta(Title,Tags,new ArrayList<Resposta>(),new HashMap<String,Resposta>(),answerCount, Id, ownerUser,data));
                 }else if (Type == 2){
                         String parentId ="";
                         int score = 0;
                         int comments = 0;
                         
                         parentId = startElement.getAttributeByName(new QName("ParentId")).getValue();
                         score = Integer.parseInt(startElement.getAttributeByName(new QName("Score")).getValue());
                         at = startElement.getAttributeByName(new QName("CommentCount"));
                         if(at!=null)
                         comments = Integer.parseInt(at.getValue());
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
         factory.createXMLEventReader(new FileInputStream(path + "Tags.xml"));

         while(eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
            
            switch(event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                  StartElement startElement = event.asStartElement();
                  String qName = startElement.getName().getLocalPart();

               if (qName.equalsIgnoreCase("row")) {
                 String Id = "";
                 String Name = "";
                   
                 Id = startElement.getAttributeByName(new QName("Id")).getValue();
                 Name = startElement.getAttributeByName(new QName("TagName")).getValue();
                 this.e.addTag(Name,Id);
               }
               break;
           }
         
        }
        
        
    }  
}